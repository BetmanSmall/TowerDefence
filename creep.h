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
//    int speed;
//    int type;

    int currX, currY;
    int lastX, lastY;

    int animationCurrIter;
    int animationMaxIter;

    QPixmap pixmap;
    std::vector<QPixmap> walkPixmaps;

    DefaultUnit* defUnit;

    Creep();

    QPixmap getAnimationInformation(int *lastX, int *lastY, int *animationCurrIter, int *animationMaxIter);
};

#endif // CREEP_H
