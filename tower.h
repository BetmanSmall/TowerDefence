#ifndef TOWER_H
#define TOWER_H

#include <QPixmap>

#include "defaulttower.h"

/**
 * @brief The Tower class - класс, описывающий общие характеристики башни.
 */
class Tower
{
//private:
public:
    QString name;
    int attack;
    int radius;
    int size;
    int type;

    int currX, currY;
    int attackX, attackY;

    QPixmap pixmap;

    DefaultTower* defTower;

    Tower();
//    Tower(int type, int radius, int attack, QPixmap pixmap);
};

#endif // TOWER_H
