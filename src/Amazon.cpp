#include "graphics.hpp"
#include "Amazon.hpp"

#include <iostream>

using namespace std;
using namespace genv;


Amazon::Amazon(Application * parent, int x, int y, int sx, int sy,
               std::function<void(Amazon*)> ram_kattintottak, 
               /* std::function<void(int, int)> shootTo, */ bool team):
               Widget(parent, x,y,sx,sy), ram_kattintottak(ram_kattintottak),
               team(team), selected(false), wantsToMove(false), wantsToShoot(false){}

void Amazon::Draw(){
    if(team){
        gout << move_to(x+10, y+10) << color(0,200,200) << box(wid-20, hei-20);
        if(selected){
            gout << move_to(x+10, y+10) << color(0,250,250) << box(wid-20, hei-20);
        }
    }
    else{
        gout << move_to(x+10, y+10) << color(200,200,0) << box(wid-20, hei-20);
        if(selected){
            gout << move_to(x+10, y+10) << color(250,250,0) << box(wid-20, hei-20);
        }
    }
}

void Amazon::Handle(genv::event ev){
    if(Widget::IsSelected(ev.pos_x, ev.pos_y)){
        if(ev.button == btn_left){
            // checkPositon(x, y);
            ram_kattintottak(this);
            wantsToMove = true;
        }
    }
}

bool Amazon::IsSelected(int posx, int posy){
    selected = Widget::IsSelected(posx, posy);
    return selected; 
}

void Amazon::MoveTo(int inx, int iny){
    bool canMove = false;
    if(x == inx){
        canMove = true;
    }
    if(y == iny){
        canMove = true;
    }
    if(x+y == inx+iny){
        canMove = true;
    }
    if(x-y == inx-iny){
        canMove = true;
    }
    if(canMove){
        x = inx;
        y = iny;
        wantsToMove = false;
        wantsToShoot = true;
    }
}

bool Amazon::WantsToMove(){
    return wantsToMove;
}

bool Amazon::WantsToShoot(){
    return wantsToShoot;
}

bool Amazon::WhichTeam(){
    return team;
}