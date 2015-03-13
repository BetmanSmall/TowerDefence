#ifndef TOWERS_H
#define TOWERS_H

#include <stdlib.h>

#include <QDebug>
#include <QPixmap>

#include "tower.h"

using namespace std;

//class Tower
//{
//public:
//    int type;
//    int radius;
//    int attack;
//    int currX, currY;
//    QPixmap pixmap;
//};

class Towers
{
    Tower* towers;

    QPixmap defaultPixmapForTower;

    int size;
    int amount;

public:
    Towers():towers(NULL) {}

    ~Towers() {deleteField();}

    void createField(int size);
    void deleteField();

    int getSize();
    int getAmount();

    Tower* getTower(int number);
    Tower* createTower(int x, int y, int type = 0);
    Tower* createTower(int x, int y, Tower tower);
    bool deleteTower(int &x, int &y);

    void setDefaulPixmapForTower(QPixmap pixmap);
    QPixmap getTowerPixmap(int x, int y);
};

#endif // TOWERS_H
