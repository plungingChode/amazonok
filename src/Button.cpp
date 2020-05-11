#include "Button.hpp"
#include "graphics.hpp"
#include "Widget.hpp"

#include <string>
#include <iostream>

using namespace std;
using namespace genv;

Button::Button(Application * parent, int x, int y, int sx, int sy, std::string caption, function<void()> action):
                Widget(parent, x, y, sx, sy), caption(caption), action(action), pushed(false){}

void Button::Draw(){
    gout << color(255, 255, 255);
    if(pushed){
        gout << color(102, 255, 153);
    }
    gout << move_to(x,y)  << box(wid, hei)
         << move_to(x+3,y+gout.cascent()+1) << color(0,0,0) << text(caption);
}

void Button::Handle(genv::event ev){
    if(Widget::IsSelected(ev.pos_x, ev.pos_y)){
            if(ev.button == btn_left){
                pushed = true;
            }
            if(ev.button == -btn_left){
                pushed = false;
                action();
            }
    }
}



bool Button::IsSelected(int posx, int posy){
    pushed = Widget::IsSelected(posx, posy);
    return pushed;
}
