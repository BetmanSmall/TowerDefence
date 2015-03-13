#ifndef TOWER_H
#define TOWER_H

#include <QPixmap>

class Tower
{
//private:
public:
    int type;
    int radius;
    int attack;
    int currX, currY;
    QPixmap pixmap;

    Tower();
    Tower(int type, int radius, int attack, QPixmap pixmap);
};

#endif // TOWER_H
