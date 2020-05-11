#include "Field.hpp"

#include <iostream>

using namespace std;
using namespace genv;

Field::Field(Application * parent, int x, int y, int sx, int sy, int cx_, int cy_,
             bool color, std::function<void(int, int)> onClick_):
            Widget(parent,x,y,sx,sy), cx(cx_), cy(cy_), isBlack(color), 
            onClick(onClick_), pushed(false), highlight(false), arrow(false)
{
}

void Field::Draw(){
    int r, g, b;
    float tint_factor = 0.3f;
    if (arrow) {
        r = 230;
        g = b = 50;
    }
    else if (pushed || highlight) {
        r = b = 80;
        g = 20;
    }
    else {
        r = g = b = 0;
        tint_factor = 0.9f;
    }
    r = r + (255 - r) * tint_factor*(!isBlack);
    g = g + (255 - g) * tint_factor*(!isBlack);
    b = b + (255 - b) * tint_factor*(!isBlack);

    gout << color(r, g, b) << move_to(x, y)<< box(wid, hei);    
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