#include "graphics.hpp"
#include "Widget.hpp"
#include "Application.hpp"
#include "SetNum.hpp"
#include "Button.hpp"
#include "Amazon.hpp"
#include "Arrow.hpp"
#include "Field.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include <cmath>

using namespace std;
using namespace genv;

class Amazons : public Application{
protected:
    SetNum *setBoardSize, *setAmazonNum;
    Button *playButton, *vsBotButton;

    vector<vector<int>> hatter = 
    {{0, 0, 0, 0},
     {0, 0, 1, 0},
     {0, 0, 3, 3},
     {0, 0, 3, 2}};

    vector<Field *> fields;
    vector<Amazon *> amazons;
    /* vector<vector<Field *>> _Fields;
    vector<Amazon *> _Amazons;
    vector<Arrow *> _Arrows;  */
    int state = 0;
    int boardSize = 0;
    int maxAmazons = 0;
    bool moveAmazon = false;
    bool shootAmazon = false;
    bool teamMoves = false;
    bool teamShoots = false;
    bool setup = true;

    Amazon *kival = nullptr;
    int allapot = 0;
    bool egyik_jatekos = true;

public:
    Amazons(int Wid, int Hei): Application(Wid, Hei){}

    void vkire_kattintottak(Amazon* a)
    {
        kival = a;

        // ha tud mozogni:
        allapot = 1; // kijeloltek vkit --> mozoghat

        printf("%p\n", (void*)a);
    }

    void field_kattintas(int x, int y)
    {
        if (allapot == 2) // lojon, ha elerheto a mezo
        {
            // ide helyezunk egy lovest
            hatter[x][y] = 3;
            allapot = 0;
            egyik_jatekos = !egyik_jatekos;

            // itt megnezni, h nyert-e valaki
        }

        if (allapot == 1) // engedjen mozogni, ha elerheto a mezo
        {
            // 'kival' koordinatai alapjan megnezni, h tud-e >ide< mozogni

            //  ha igen
            //  hatter[kival.x][kival.y] = 0;
            //  kival->MoveTo(x, y);
                hatter[x][y] = 1; // v. 2, ha a masik jatekos
                allapot = 2; // most lehessen loni
        }
    }

    void Menu(){
        setBoardSize = new SetNum(this, 250, 300, 100, 30, 6, 12);
        setAmazonNum = new SetNum(this, 250, 340, 100, 30, 1, 4);
        function<void()> play = [=](){
            widgets.clear();
            state = 1;
            boardSize = setBoardSize->GetValue();
            StateCheck();
        };
        playButton = new Button(this, 250, 150, 100, 30, "Play", play);
        /* vsBotButton = new Button(this, 250, 190, 100, 30, "VS Bot"); */
    }


    void Setup(){
        double calculate = wid/boardSize, fieldSize;
        fieldSize = floor(calculate);

        function<void(int, int)> checkPosition = [=](int cx, int cy){
            for(Field * f : fields){
                f->ColorThis(cx, cy);
                setup = false;
            }
            moveAmazon = true;
        };

        // if(maxAmazons < setAmazonNum->GetValue()*2){setup = true;}

        // function<void(int, int)> newAmazon = [=](int cx, int cy){
        //     if(maxAmazons == setAmazonNum->GetValue()*2){setup = false;}
        //     if(maxAmazons < setAmazonNum->GetValue()*2){setup = true;}
            
        //     if((maxAmazons < setAmazonNum->GetValue()*2) && setup){
        //         Amazon *amazon = new Amazon(this, cx, cy, fieldSize, fieldSize, checkPosition, teamMoves);
        //         amazons.push_back(amazon);
        //         teamMoves = !teamMoves;
        //         maxAmazons +=1;
        //     }
            
        //     if(moveAmazon && !setup){  
        //         for(Amazon * a : amazons){
        //             if(a->WantsToMove() && a->WhichTeam() == teamMoves){
        //                 a->MoveTo(cx,cy);
        //                 teamMoves = !teamMoves;
        //                 shootAmazon = true;
        //                 break;
        //             }
        //         }
        //         moveAmazon = false;
        //     }
            
        //     if(shootAmazon && !setup){  
        //         for(Amazon * a : amazons){
        //             if(a->WantsToShoot() && a->WhichTeam() == teamShoots){
        //                 a->ShootTo(cx,cy);
        //                 teamMoves = !teamMoves;
        //                 shootAmazon = false;
        //                 break;
        //             }
        //         }
        //     }
        // };

        for(int i = 0;i<boardSize;i++){
            for(int j = 0;j<boardSize;j++){
                Field *F = new Field(this, i*fieldSize, j*fieldSize, fieldSize, fieldSize, (i+j)%2, [=](int x, int y) { field_kattintas(x, y); });
                fields.push_back(F);
            }
        }

        Amazon *amazon = new Amazon(this, 1, 1, fieldSize, fieldSize, [=](Amazon* a) { vkire_kattintottak(a); }, teamMoves);
        amazons.push_back(amazon);
    }

    void Play(){}
    
    void GameOver(){}

    void Action(string param){
    }

    void StateCheck(){
        switch (state)
        {
        case 0:
            Menu();
            Amazons::EventLoop();
            break;
        case 1:
            Setup();
            Amazons::EventLoop();
            break;
        case 2:
            /* Play(); */
            Amazons::EventLoop();
            break;
        case 9:
            GameOver();
            Amazons::EventLoop();
            break;    
        default:
            break;
        }
    }
};


int main(){
    Amazons Game(600, 600);
    Game.StateCheck();
    
    return 0;
}

/*     gout.open(400,400);
     gout << color(255, 200, 170) << move_to(20,20) << box(20,20) << refresh; 
    event ev;
    int x = 0;
    while (gin>> ev)
    {
        if(ev.pos_x > 20 && ev.pos_x < 40 && ev.pos_y > 20 && ev.pos_y < 40){
            x += 1;
            cout << "benne van" << x <<'\n';
        }
    }
     */