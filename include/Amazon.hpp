#ifndef AMAZON_HPP_INCLUDED
#define AMAZON_HPP_INCLUDED

#include "Widget.hpp"
#include <functional>

class Amazon : public Widget{
    protected:
        std::function<void(Amazon*)> ram_kattintottak;
        std::function<void(int, int)> checkPositon;
        std::function<void(int, int)> shootTo;
        bool team, selected, wantsToMove, wantsToShoot;
    public:
        Amazon(Application * parent, int x, int y, int sx, int sy,
              std::function<void(Amazon*)> ram_kattintottak, /* std::function<void(int, int)> shootTo, */ bool team);
        virtual void Draw();
        virtual void Handle(genv::event ev);
        virtual bool IsSelected(int posx, int posy);
        virtual bool WantsToMove();
        virtual bool WantsToShoot();
        virtual void MoveTo(int cx, int cy);
        /* virtual void ShootTo(int cx, int cy); */
        virtual bool WhichTeam();
};

#endif
