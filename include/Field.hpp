#ifndef FIELD_HPP_INCLUDED
#define FIELD_HPP_INCLUDED

#include "Widget.hpp"
#include <functional>

class Field : public Widget{
protected:
    int cx, cy;
    bool isBlack, pushed, highlight, arrow;
    std::function<void(int, int)> onClick;

public:
    Field(Application * parent, int x, int y, int sx, int sy, int cx, int cy,
          bool isBlack, std::function<void(int, int)> onClick);
    
    int CoordX() const { return cx; }
    int CoordY() const { return cy; }

    // Ha val == true, lilara szinezi, prio 2
    void SetHighlight(bool val) { highlight = val; }
    
    // Ha val == true, pirosra szinezi, prio 1
    void SetArrow(bool val) { arrow = val; }

    void Draw();
    void Handle(genv::event ev);
};

#endif