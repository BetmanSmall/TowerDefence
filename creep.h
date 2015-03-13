#ifndef CREEP_H
#define CREEP_H

#include <QPixmap>

#include "defaultunit.h"

class Creep
{
public:
//    int type;
    int number;
//    int speed;
    int currX, currY;
    int hp;
    bool alive;
    QPixmap pixmap;

    DefaultUnit* defUnit;

    Creep();
};

#endif // CREEP_H
