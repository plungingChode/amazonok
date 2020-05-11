#ifndef FIELD_HPP_INCLUDED
#define FIELD_HPP_INCLUDED

#include "Widget.hpp"
#include <functional>

class Field : public Widget{
    protected:
        int coordX, coordY;
        bool hasAmazon, hasArrow, colorBool, pushed;
        std::function<void(int, int)> kattintasra;
    public:
        Field(Application * parent, int x, int y, int sx, int sy, bool colorIndex, std::function<void(int, int)> newAmazon);
        void Draw();
        void Handle(genv::event ev);
        bool HaveArrow();
        bool HaveAmazon();
        bool NewAmazon(int cx, int cy);
        virtual bool IsSelected(int posx, int posy);
        void ColorThis(int inx, int iny);
        bool IsColored(int inx, int iny);
};

#endif