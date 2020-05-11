#ifndef WIDGET_HPP_INCLUDED
#define WIDGET_HPP_INCLUDED

#include "graphics.hpp"
#include "Application.hpp"

#include <string>

class Widget{
    protected:
        int x, y, wid, hei;
        Application * parent;
    public:
        Widget(Application * parent, int x, int y, int wid, int hei);
        virtual bool IsSelected(int mouse_x, int mouse_y);
        virtual void Draw() = 0;
        virtual void Handle(genv::event ev) = 0;
};

#endif