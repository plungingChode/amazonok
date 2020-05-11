#include "Widget.hpp"
#include "graphics.hpp"

#include <string>


Widget::Widget(Application * parent, int x, int y, int wid, int hei):
                parent(parent), x(x), y(y), wid(wid), hei(hei)
                {
                    parent->RegisterWidget(this);
                }

bool Widget::IsSelected(int posx, int posy){
    return posx>x && posx<x+wid && posy>y && posy<y+hei;
}
