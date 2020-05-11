#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include "Widget.hpp"
#include <string>
#include <functional>

class Button : public Widget{
    protected:
        std::string caption;
        std::function<void()> action;
        bool pushed;
    public:
        Button(Application * parent, int x, int y, int sx, int sy, std::string caption, std::function<void()> action);
        ~Button(){}
        virtual void Draw();
        virtual void Handle(genv::event ev);
        virtual bool IsSelected(int posx, int posy);
};

#endif