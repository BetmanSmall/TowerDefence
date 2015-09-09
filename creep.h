#ifndef CREEP_H
#define CREEP_H

#include <QPixmap>

#include "defaultunit.h"

enum Direction
{
    DirectionUp,
    DirectionUpRight,
    DirectionRight,
    DirectionDownRight,
    DirectionDown,
    DirectionDownLeft,
    DirectionLeft,
    DirectionUpLeft
};

/**
 * @brief The Creep class - класс, описывающий общие характеристики крипа.
 */
class Creep
{
public:
    int hp;
    bool alive;
    bool preDeath;
    int number;
//    int speed;
//    int type;

    int coorByCellX, coorByCellY;
    int coorByMapX, coorByMapY;

    int lastX, lastY;

    Direction direction;

    int animationCurrIter;
    int animationMaxIter;

    QPixmap pixmap;
    std::vector<QPixmap> activePixmaps;

    DefaultUnit* defUnit;

    Creep();

    QPixmap getAnimationInformation(int *lastX, int *lastY, int *animationCurrIter, int *animationMaxIter);
    bool takeDamage(int damage);
};

#endif // CREEP_H
