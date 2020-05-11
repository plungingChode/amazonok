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
           std::function<void(Amazon*)> onClick, bool team);

    int CoordX() const { return cx; }
    int CoordY() const { return cy; }
    bool Team() const { return blueTeam; }

    // Ha val == true, tesz kore egy keretet
    void SetSelected(bool val) { selected = val; }

    virtual void Draw();
    virtual void Handle(genv::event ev);
    virtual void MoveTo(int x, int y, int cx, int cy);
};

#endif
