#ifndef SETNUM_HPP_INCLUDED
#define SETNUM_HPP_INCLUDED

#include "Widget.hpp"

#include <string>

class SetNum : public Widget{
    protected:
        int value, lowerLimit, upperLimit;
        bool focused;
    public:
        SetNum(Application * parent, int x, int y, int sx, int sy, int lowerlim, int upperlim);
        virtual void Draw();
        virtual bool IsSelected(int posx, int posy);
        virtual void Handle(genv::event ev);
        int GetValue();
};

#endif