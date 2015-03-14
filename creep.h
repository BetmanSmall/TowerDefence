#ifndef CREEP_H
#define CREEP_H

#include <QPixmap>

#include "defaultunit.h"

class Creep
{
public:
    int hp;
    bool alive;
    int number;
    int animationCurrIter;
    int animationMaxIter;
//    int speed;
//    int type;

    int currX, currY;
    int lastX, lastY;

    QPixmap pixmap;
    std::vector<QPixmap> walkPixmaps;

    DefaultUnit* defUnit;

    Creep();
};

#endif // CREEP_H
