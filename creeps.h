#ifndef CREEPS_H
#define CREEPS_H

#include <stdlib.h>

#include <QPixmap>

//#include "defaultunit.h"
#include "creep.h"

//class Creep
//{
//public:
//    int type;
//    int number;
////    int speed;
//    int currX, currY;

//    int hp;
//    bool alive;
//    QPixmap pixmap;
//};

class Creeps
{
    Creep* creeps;

    QPixmap defaultPixmapForCreep;

    int size;
    int amount;

public:
    Creeps():creeps(NULL) {}

    ~Creeps() {deleteMass();}

    void createMass(int newSize);
    void deleteMass();

    int getSize();
    int getAmount();
    int getHP(int x, int y);

    bool attackCreep(int x, int y, int hp, Creep* creep);

    Creep* getCreep(int number);
    Creep* getCreep(int x, int y);
    Creep* createCreep(int x, int y, DefaultUnit* unit);

    void setDefaulPixmapForCreep(QPixmap pixmap);
    QPixmap getCreepPixmap(int x, int y);
};

#endif // CREEPS_H
