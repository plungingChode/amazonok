#ifndef FIELD_HPP_INCLUDED
#define FIELD_HPP_INCLUDED

#include "Widget.hpp"
#include <functional>

class Field : public Widget{
    protected:
        int cx, cy;
        bool isBlack, pushed, highlight;
        std::function<void(int, int)> onClick;
    public:
        Field(Application * parent, int x, int y, int sx, int sy, int cx, int cy,
              bool isBlack, std::function<void(int, int)> onClick);
        
        int coordX() const { return cx; }
        int coordY() const { return cy; }
        void set_highlight(bool val) { highlight = val; }

        void Draw();
        void Handle(genv::event ev);
};

#endif