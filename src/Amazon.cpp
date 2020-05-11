#include "graphics.hpp"
#include "Amazon.hpp"

#include <iostream>

using namespace std;
using namespace genv;

Amazon::Amazon(Application * parent, int x, int y, int sx, int sy, int cx_, int cy_,
               std::function<void(Amazon*)> onClick_, bool blueTeam_):
               Widget(parent, x,y,sx,sy), cx(cx_), cy(cy_), onClick(onClick_),
               blueTeam(blueTeam_), selected(false)
{
}

void Amazon::Draw() {
    // kicsit egyszerusitve, ugyis u.a. a ket szinkod
    int c = 230;
    if (selected)
    {
        // lila keret
        gout << move_to(x-4, y-4) << color(230, 0, 230) << box(wid+8, hei+8);
    }
    if(blueTeam) {
        gout << color(0, c, c);
    }
    else {
        gout << color(c, c, 0);
    }
    gout << move_to(x, y) << box(wid, hei);
}

void Amazon::Handle(genv::event ev) {
    if(IsSelected(ev.pos_x, ev.pos_y) && ev.button == -btn_left) {
        onClick(this);
    }
}

void Amazon::MoveTo(int new_x, int new_y, int new_cx, int new_cy) {
    x = new_x;
    y = new_y;
    cx = new_cx;
    cy = new_cy;
}