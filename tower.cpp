#include "tower.h"

Tower::Tower()
{
}

Tower::Tower(int type, int radius, int attack, QPixmap pixmap)
{
    this->type = type;
    this->radius = radius;
    this->attack = attack;
    this->pixmap = pixmap;
}
