#ifndef AMAZON_HPP_INCLUDED
#define AMAZON_HPP_INCLUDED

#include "Widget.hpp"
#include <functional>

class Amazon : public Widget{
    protected:
        int cx, cy;
        std::function<void(Amazon*)> onClick;
        bool blueTeam, selected;

    public:
        Amazon(Application * parent, int x, int y, int sx, int sy, int cx, int cy,
              std::function<void(Amazon*)> ram_kattintottak, bool team);

        int coordX() const { return cx; }
        int coordY() const { return cy; }
        bool team() const { return blueTeam; }

        void setSelected(bool val) { selected = val; }

        virtual void Draw();
        virtual void Handle(genv::event ev);
        virtual void MoveTo(int x, int y, int cx, int cy);
};

#endif
