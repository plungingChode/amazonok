#include "Arrow.hpp"

Arrow::Arrow(Application * parent, int x, int y, int sx, int sy, int arposx, int arposy):
            Widget(parent, x,y,sx,sy), coordX(arposx), coordY(arposy){}

void Arrow::shoot(int posx, int posy){}