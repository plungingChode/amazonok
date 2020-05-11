#include "graphics.hpp"
#include "Widget.hpp"
#include "Application.hpp"
#include "SetNum.hpp"
#include "Button.hpp"
#include "Amazon.hpp"
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
    // statuszkodok
    enum status_t
    {
        BEGIN = 0,
        SELECT,
        MOVE,
        SHOOT,
        END
    };

    // mezok tipusai
    enum cell_t
    {
        HIGHLIGHT = -1,
        EMPTY = 0,
        P1 = 1,
        P2 = 2,
        ARROW = 3,
    };

    SetNum *setBoardSize, *setAmazonNum;
    Button *playButton, *vsBotButton;

    vector<vector<int>> board = 
    {{1, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 2}};

    vector<vector<Field *>> fields;
    vector<Amazon *> p1Amazons, p2Amazons;
    int boardSize = 0;
    bool setup = true;
    int fieldSize;

    Amazon *activeAmazon = nullptr;
    int status = BEGIN;
    bool currentTeam = true;

public:
    Amazons(int Wid, int Hei): Application(Wid, Hei) { }

    // Adott pont a tablan van-e?
    bool IsInBounds(int x, int y)
    {
        return x >= 0 && x < boardSize && y >= 0 && y < boardSize;
    }

    // Adott pont ures-e? (erteke 0)
    bool IsFree(int x, int y)
    {
        return board[x][y] == EMPTY;
    }

    // Adott pont ki van-e jelolve? (erteke -1)
    bool IsHighlight(int x, int y)
    {
        return board[x][y] == HIGHLIGHT;
    }

    // Adott pont es hozza tartozo mezo kijelolese.
    void Highlight(int x, int y)
    {
        board[x][y] = HIGHLIGHT;
        fields[x][y]->SetHighlight(true);
    }

    // Minden kijeloles torlese.
    void ClearHighlight()
    {
        for (int x = 0; x < boardSize; x++) {
            for (int y = 0; y < boardSize; y++) {
                if (IsHighlight(x, y)) {
                    board[x][y] = EMPTY;
                }
                fields[x][y]->SetHighlight(false);
            }
        }
    }

    // Adott iranyban megnezi, van-e elerheto ures mezo. 
    // Ha 'doHighlight', akkor az elerheto mezoket kijeloli.
    bool CheckDirection(int x, int y, int dx, int dy, bool doHighlight)
    {
        bool hasFree = false;
        x += dx;
        y += dy;
        while(IsInBounds(x, y) && IsFree(x, y))
        {
            if (doHighlight) Highlight(x, y);
            hasFree = true;
            x += dx;
            y += dy;
        }
        return hasFree;
    }

    // Megnezi mind a 8 iranyban, hogy van-e elerheto ures mezo.
    // Ha 'doHighlight', akkor az elerheto mezoket kijeloli.
    bool CheckFree(int x, int y, bool doHighlight = true)
    {
        bool good = false;
        good |= CheckDirection(x, y,  1,  0, doHighlight);
        good |= CheckDirection(x, y, -1,  0, doHighlight);
        good |= CheckDirection(x, y,  0,  1, doHighlight);
        good |= CheckDirection(x, y,  0, -1, doHighlight);
        good |= CheckDirection(x, y,  1,  1, doHighlight);
        good |= CheckDirection(x, y,  1, -1, doHighlight);
        good |= CheckDirection(x, y, -1,  1, doHighlight);
        good |= CheckDirection(x, y, -1, -1, doHighlight);
        return good;
    }

    // Megnezi, tud-e mozogni az egyik jatekos barmely amazonja.
    bool CheckCanMove(const vector<Amazon*> &v)
    {
        for (Amazon *a : v) {
            if (!CheckFree(a->CoordX(), a->CoordY(), false)) {
                return false;
            }
        }
        return true;
    }

    // Amazon hivja meg, ha ra kattintottak
    void Amazon_OnClick(Amazon *a)
    {
        int x = a->CoordX();
        int y = a->CoordY();
        printf("[amazon katt ] %d, %d\n", x, y);

        if (status == SELECT) {
            bool sameTeam = a->Team() == currentTeam;   // csak sajat babu
            bool canMove = sameTeam && CheckFree(x, y); // nezzuk meg, merre mozoghat
            if (canMove) {
                a->SetSelected(true);
                activeAmazon = a;
                status = MOVE;

                printf("[amazon kival] %d, %d\n", x, y);
                printf("[status valt ] SEL >> MOV\n");
            } else if (!sameTeam) {
                printf("[amazon katt ] masik csapat\n");
            } else if (!canMove) {
                printf("[amazon katt ] nem tud mozogni\n");
            }
        }
    }

    // Mezo hivja meg, ha rakattintottak
    void Field_OnClick(int x, int y)
    {
        printf("[mezore katt ] %d, %d\n", x, y);
        if (status == SHOOT && IsHighlight(x, y)) // csak a megjelolt mezokre lohet
        {
            board[x][y] = ARROW;
            fields[x][y]->SetArrow(true);
            
            // loves utan nincs kivalasztott -> toroljuk
            activeAmazon->SetSelected(false);
            activeAmazon = nullptr;

            status = SELECT;
            currentTeam = !currentTeam;

            // totroljuk a megjelolt mezoket
            ClearHighlight();

            // nezzuk meg, nyert-e valaki
            if (!CheckCanMove(p1Amazons)) {
                status = END;
                printf("[status valt ] SHT >> END\n");
                printf("[status      ] P2 win\n");
            } else if (!CheckCanMove(p2Amazons)) {
                status = END;
                printf("[status valt ] SHT >> END\n");
                printf("[status      ] P1 win\n");
            }
        }

        if (status == MOVE && IsHighlight(x, y)) { // csak a megjelolt mezokre lephet
                int regi_x = activeAmazon->CoordX();
                int regi_y = activeAmazon->CoordY();

                board[regi_x][regi_y] = EMPTY;
                board[x][y] = currentTeam ? P1 : P2; // player 1 = 'true', player 2 = 'false'
                activeAmazon->MoveTo(x*fieldSize+10, y*fieldSize+10, x, y);

                printf("[amazon mozog] (%d, %d) >> (%d, %d)\n", regi_x, regi_y, x, y);

                ClearHighlight();
                if (CheckFree(x, y)) { // ha van hova loni, lojon (kotelezo loni?)
                    status = SHOOT;
                    printf("[status valt ] MOV >> SHT\n");
                }
                else { // ha nincs, akkor a masik jatekos jon (van ilyen?)
                    activeAmazon->SetSelected(false);
                    activeAmazon = nullptr;

                    status = SELECT;
                    currentTeam = !currentTeam;

                    printf("[status valt ] MOV >> SEL\n");
                    printf("[amazon kival] torolve\n");
                }
        }
    }

    void Menu() {
        setBoardSize = new SetNum(this, 250, 300, 100, 30, 6, 12);
        setAmazonNum = new SetNum(this, 250, 340, 100, 30, 1, 4);
        function<void()> play = [=](){
            widgets.clear();
            status = SELECT;
            // v ~~~~~~~ ezt majd mashogy
            // boardSize = setBoardSize->GetValue(); 
            Setup();
        };
        playButton = new Button(this, 250, 150, 100, 30, "Play", play);
        /* vsBotButton = new Button(this, 250, 190, 100, 30, "VS Bot"); */
        EventLoop();
    }


    void Setup() {
        // a 'board' valtoztatsaval modosithato
        boardSize = board.size();
        fieldSize = wid/boardSize; // sztem ide nem kell a floor, ugy tudom
                                   // az int osztas alapbol lefele kerekit

        // 'Field'eket matrixban, h konnyeb legyen keresni
        fields = vector<vector<Field *>>(boardSize, vector<Field*>(boardSize));
        std::function<void(int, int)> fieldCallback = [=](int x, int y)
        {
            Field_OnClick(x, y);
        };
        for(int x = 0;x<boardSize;x++) {
            for(int y = 0;y<boardSize;y++) {
                // erdemes kulon felvenni ezeket, igy kicsit atlathatobb
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
            Amazon_OnClick(a);
        };
        for (int x = 0; x < boardSize; x++) {
            for (int y = 0; y < boardSize; y++) {
                // az amazonok szamat es helyet a 'board'-rol olvassuk le
                if(board[x][y] != 0)
                {
                    bool isPlayer1 = (board[x][y] == P1);
                    int pos_x = x * fieldSize + 10;
                    int pos_y = y * fieldSize + 10;
                    int size = fieldSize - 20;

                    Amazon *a = new Amazon(this, pos_x, pos_y, size, size, x, y, amazonCallback, isPlayer1);
                    if (isPlayer1) {
                        p1Amazons.push_back(a);
                    } else {
                        p2Amazons.push_back(a);
                    }
                }
            }
        }
    }
    void Action(string param) { }
};


int main(){
    Amazons Game(600, 600);
    Game.Menu();
    
    return 0;
}