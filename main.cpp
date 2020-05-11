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
    enum status_t
    {
        BEGIN,
        SELECT,
        MOVE,
        SHOOT,
        END
    };

    enum player_t
    {
        EMPTY = 0,
        P1 = 1,
        P2 = 2,
        ARROW = 3
    };

    SetNum *setBoardSize, *setAmazonNum;
    Button *playButton, *vsBotButton;

    vector<vector<int>> hatter = 
    {{1, 1, 0, 0, 0, 0},
     {1, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 2},
     {0, 0, 0, 0, 2, 2}};

    vector<vector<Field *>> fields;
    vector<Amazon *> amazons;
    int boardSize = 0;
    int maxAmazons = 0;
    bool setup = true;
    int fieldSize;

    Amazon *activeAmazon = nullptr;
    int status = BEGIN;
    bool currentTeam = false;

public:
    Amazons(int Wid, int Hei): Application(Wid, Hei){}

    bool inBounds(int x, int y)
    {
        return x >= 0 && x < boardSize && y >= 0 && y < boardSize;
    }

    bool isFree(int x, int y)
    {
        return hatter[x][y] == 0;
    }

    bool isHighlight(int x, int y)
    {
        return hatter[x][y] == -1;
    }

    void highlight(int x, int y)
    {
        hatter[x][y] = -1;
        fields[x][y]->setHighlight(true);
    }

    void clearHighlight()
    {
        for (int x = 0; x < boardSize; x++) {
            for (int y = 0; y < boardSize; y++) {
                if (isHighlight(x, y)) {
                    hatter[x][y] = 0;
                }
                fields[x][y]->setHighlight(false);
            }
        }
    }

    bool checkDirection(int x, int y, int dx, int dy)
    {
        bool hasFree = false;
        x += dx;
        y += dy;
        while(inBounds(x, y) && isFree(x, y))
        {
            highlight(x, y);
            hasFree = true;
            x += dx;
            y += dy;
        }
        return hasFree;
    }

    bool checkFree(int x, int y)
    {
        bool good = false;
        good |= checkDirection(x, y,  1,  0);
        good |= checkDirection(x, y, -1,  0);
        good |= checkDirection(x, y,  0,  1);
        good |= checkDirection(x, y,  0, -1);
        good |= checkDirection(x, y,  1,  1);
        good |= checkDirection(x, y,  1, -1);
        good |= checkDirection(x, y, -1,  1);
        good |= checkDirection(x, y, -1, -1);
        return good;
    }

    void amazon_onClick(Amazon *a)
    {        
        int x = a->coordX();
        int y = a->coordY();
        printf("[amazon katt ] %d, %d\n", x, y);

        bool sameTeam = a->team() == currentTeam;
        bool canMove = sameTeam && checkFree(x, y);
        if (status == SELECT && sameTeam && canMove) {
            a->setSelected(true);

            activeAmazon = a;
            printf("[amazon kival] %d, %d\n", x, y);

            status = MOVE; // kijeloltek vkit --> mozoghat
            printf("[status valt ] SEL >> MOV\n");
        } else if (!sameTeam) {
            printf("[amazon katt ] masik csapat\n");
        } else if (!canMove) {
            printf("[amazon katt ] nem tud mozogni\n");
        }
    }

    void field_onClick(int x, int y)
    {
        printf("[mezore katt ] %d, %d\n", x, y);
        if (status == SHOOT && isHighlight(x, y)) // lojon, ha elerheto a mezo
        {
            hatter[x][y] = ARROW;
            status = SELECT;
            currentTeam = !currentTeam;
            fields[x][y]->setArrow(true);
            activeAmazon->setSelected(false);
            activeAmazon = nullptr;
            clearHighlight();

            // itt megnezni, h nyert-e valaki
        }

        if (status == MOVE && isHighlight(x, y)) {
                int regi_x = activeAmazon->coordX();
                int regi_y = activeAmazon->coordY();

                hatter[regi_x][regi_y] = 0;
                hatter[x][y] = 2 - currentTeam; 
                activeAmazon->MoveTo(x*fieldSize+10, y*fieldSize+10, x, y);
                printf("[amazon mozog] (%d, %d) >> (%d, %d)\n", regi_x, regi_y, x, y);

                clearHighlight();
                if (checkFree(x, y)) {
                    status = SHOOT; // most lehessen loni
                    printf("[status valt ] MOV >> SHT\n");
                }
                else {
                    status = SELECT;
                    printf("[status valt ] MOV >> SEL\n");
                    
                    activeAmazon->setSelected(false);
                    activeAmazon = nullptr;
                    printf("[amazon kival] torolve\n");

                    currentTeam = !currentTeam;
                }
        }
    }

    void Menu(){
        setBoardSize = new SetNum(this, 250, 300, 100, 30, 6, 12);
        setAmazonNum = new SetNum(this, 250, 340, 100, 30, 1, 4);
        function<void()> play = [=](){
            widgets.clear();
            status = SELECT;
            boardSize = setBoardSize->GetValue();
            Setup();
        };
        playButton = new Button(this, 250, 150, 100, 30, "Play", play);
        /* vsBotButton = new Button(this, 250, 190, 100, 30, "VS Bot"); */
    }


    void Setup(){
        double calculate = wid/boardSize;
        fieldSize = floor(calculate);

        fields = vector<vector<Field *>>(boardSize, vector<Field*>(boardSize));
        std::function<void(int, int)> fieldCallback = [=](int x, int y)
        {
            field_onClick(x, y);
        };
        for(int x = 0;x<boardSize;x++){
            for(int y = 0;y<boardSize;y++){
                int pos_x = x*fieldSize;
                int pos_y = y*fieldSize;
                int size = fieldSize;
                bool isBlack = (x+y)%2;

                Field *f = new Field (this, pos_x, pos_y, size, size, x, y, isBlack, fieldCallback);
                fields[x][y] = f;
            }
        }

        std::function<void(Amazon*)> amazonCallback = [=](Amazon* a)
        {
            amazon_onClick(a);
        };

        for (int x = 0; x < boardSize; x++) {
            for (int y = 0; y < boardSize; y++) {
                if(hatter[x][y] != 0)
                {
                    bool isPlayer1 = (hatter[x][y] == P1);
                    int pos_x = x * fieldSize + 10;
                    int pos_y = y * fieldSize + 10;
                    int size = fieldSize - 20;

                    Amazon *a = new Amazon(this, pos_x, pos_y, size, size, x, y, amazonCallback, isPlayer1);
                    amazons.push_back(a);
                }
            }
        }
    }

    void Play(){}
    
    void GameOver(){}

    void Action(string param){
    }

    void StateCheck(){
        switch (status)
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