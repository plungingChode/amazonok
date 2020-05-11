#include "Application.hpp"
#include "graphics.hpp"
#include "Widget.hpp"

#include <iostream>

using namespace std;
using namespace genv;

bool goutOpened = false;

Application::Application(int _wid, int _hei): wid(_wid), hei(_hei){}

void Application::ClearScreen(){
    gout << move_to(0,0) << color(0,0,0) << box(wid, hei);
}

void Application::OpenGout(){
    gout.open(wid, hei);
}

void Application::Draw(vector<Widget *> widgetVect){
    ClearScreen();
    for(Widget * w : widgetVect){
        w->Draw();
    }
    gout << refresh;
}

void Application::EventLoop(){
    if(!goutOpened){
        OpenGout();
        goutOpened = true;
    }

    Draw(widgets);    

    event ev;
    while (gin >> ev){
        if(ev.type == ev_mouse && ev.button == btn_left){
            for(size_t i = 0;i<widgets.size();i++){
                if(widgets[i]->IsSelected(ev.pos_x, ev.pos_y)){
                    focusedWidget = i;
                }
            }
        }
    
        if(focusedWidget!=-1){
            widgets[focusedWidget]->Handle(ev);
        }
        
        Draw(widgets);

        if(ev.type == ev_key && ev.keycode == key_escape){
            break;
        }
     
    }
}


void Application::RegisterWidget(Widget * Widget){
    widgets.push_back(Widget);
}






