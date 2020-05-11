#include "SetNum.hpp"

#include <iostream>
#include <string>

using namespace std;
using namespace genv;

SetNum::SetNum(Application * parent, int x, int y, int sx, int sy, int lowerlimit, int upperlimit):
               Widget(parent, x, y, sx, sy), value(lowerlimit), lowerLimit(lowerlimit), upperLimit(upperlimit), 
               focused(false){}

void SetNum::Draw(){
    gout << color(255,255,255);
    if(focused){
        gout << color(102, 255, 153);
    }
    gout << move_to(x, y) << box(wid, hei) 
            << move_to(x+wid-hei/2, y) << color(100,244,255) << box(hei/2,hei/2)                     //fölső állító négyzet
            << move_to(x+wid-hei/2, y+hei/2) << color(0,0,0) << line(hei/2, 0)                       // vonal
            << move_to(x+wid-hei/2, y+hei/2+1) << color(0,204,255) << box(hei/2,hei/2-1);         // alsó állító négyzet
    gout << move_to(x+wid-hei/2+(hei/4-3), y+gout.cascent()-1) << color(0,0,0) << text("+") // +
            << move_to(x+wid-hei/2+(hei/4-3), y+hei/2+gout.cascent()-1) << text("-");       // - 
    
    gout << move_to(x + 3, y + gout.cascent()) << text(to_string(value));

}

bool SetNum::IsSelected(int posx, int posy){
    focused = Widget::IsSelected(posx, posy);
    return focused; 
}

void SetNum::Handle(genv::event ev){
    if(focused){
        if(ev.pos_x > x+wid-hei/2 && ev.pos_x < x+wid  &&
           ev.pos_y > y && ev.pos_y < y+hei/2){
               if(ev.type == ev_mouse && ev.button == btn_left){
               value = min(value+1, upperLimit);}
           }
        if(ev.pos_x > x+wid-hei/2 && ev.pos_x < x+wid  &&
           ev.pos_y > y+hei/2 && ev.pos_y < y+hei){
               if(ev.type == ev_mouse && ev.button == btn_left){
               value = max(value-1, lowerLimit);}
           }
        
        if(ev.type == ev_key && ev.keycode == key_up){
            value = min(value+1, upperLimit);
        }
        if(ev.type == ev_key && ev.keycode == key_down){
            value = max(value-1, lowerLimit);
        }
    }
}


int SetNum::GetValue(){
    return value;
}



