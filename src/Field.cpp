#include "Field.hpp"

#include <iostream>

using namespace std;
using namespace genv;

Field::Field(Application * parent, int x, int y, int sx, int sy, int cx_, int cy_,
             bool color, std::function<void(int, int)> onClick_):
            Widget(parent,x,y,sx,sy), cx(cx_), cy(cy_), isBlack(color), 
            onClick(onClick_), pushed(false), highlight(false)
{
}

void Field::Draw(){

    if(isBlack) {
        gout << color(0,0,0);    
    }
    else {
        gout << color(255,255,255);
    }
    if(pushed || highlight) {
        int r = 80 + (255 - 80) * 0.3*!isBlack;
        int g = 20 + (255 - 20) * 0.3*!isBlack;
        int b = 80 + (255 - 80) * 0.3*!isBlack;
        gout << color(r,g,b);    
    }

    gout << move_to(x, y)<< box(wid, hei);    

}

void Field::Handle(event ev){
    if(IsSelected(ev.pos_x, ev.pos_y)){
        if(ev.button == btn_left){
            pushed = true;
        }
        if(ev.button == -btn_left){
            pushed = false;
            onClick(cx, cy);
        }
    }
}