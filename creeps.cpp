#include "creeps.h"

void Creeps::createMass(int newSize)
{
    if(creeps == NULL)
    {
        creeps = new Creep[newSize];
        size = newSize;
        amount = 0;
    }
    else
    {
        deleteMass();
        createMass(newSize);
    }
}

void Creeps::deleteMass()
{
    if(creeps != NULL)
    {
        delete[] creeps;
        creeps = NULL;
    }
}

int Creeps::getSize()
{
    return size;
}

int Creeps::getAmount()
{
    return amount;
}

int Creeps::getHP(int x, int y)
{
    for(int k = 0; k < amount; k++)
    {
        int localX = creeps[k].coorByCellX;
        int localY = creeps[k].coorByCellY;

        if(localX == x && localY == y)
            return creeps[k].hp;
    }
    return 0;
}

bool Creeps::attackCreep(int x, int y, int damage, Creep *creep)
{
    for(int k = 0; k < amount; k++)
    {
        if(!creeps[k].alive)
            continue;

        int localX = creeps[k].coorByCellX;
        int localY = creeps[k].coorByCellY;

        if(localX == x && localY == y)
        {
            int localHP = creeps[k].hp;
            localHP = localHP - damage;

            if(localHP <= 0)
            {
                creeps[k].hp = 0;
//                creeps[k].coorByCellX = -1;
//                creeps[k].coorByCellY = -1;
                creeps[k].alive = false;
                creeps[k].preDeath = true;

                // ЛАЖА
                creeps[k].animationCurrIter = 0;
                Direction direction = creeps[k].direction;

                if(direction == DirectionUpLeft)
                {
                    creeps[k].animationMaxIter = creeps[k].defUnit->death_up_left.size();
                    creeps[k].activePixmaps = creeps[k].defUnit->death_up_left;
                }
                else if(direction == DirectionUp)
                {
                    creeps[k].animationMaxIter = creeps[k].defUnit->death_up.size();
                    creeps[k].activePixmaps = creeps[k].defUnit->death_up;
                }
                else if(direction == DirectionUpRight)
                {
                    creeps[k].animationMaxIter = creeps[k].defUnit->death_up_right.size();
                    creeps[k].activePixmaps = creeps[k].defUnit->death_up_right;
                }
                else if(direction == DirectionLeft)
                {
                    creeps[k].animationMaxIter = creeps[k].defUnit->death_left.size();
                    creeps[k].activePixmaps = creeps[k].defUnit->death_left;
                }
                else if(direction == DirectionRight)
                {
                    creeps[k].animationMaxIter = creeps[k].defUnit->death_right.size();
                    creeps[k].activePixmaps = creeps[k].defUnit->death_right;
                }
                else if(direction == DirectionDownLeft)
                {
                    creeps[k].animationMaxIter = creeps[k].defUnit->death_down_left.size();
                    creeps[k].activePixmaps = creeps[k].defUnit->death_down_left;
                }
                else if(direction == DirectionDown)
                {
                    creeps[k].animationMaxIter = creeps[k].defUnit->death_down.size();
                    creeps[k].activePixmaps = creeps[k].defUnit->death_down;
                }
                else if(direction == DirectionDownRight)
                {
                    creeps[k].animationMaxIter = creeps[k].defUnit->death_down_right.size();
                    creeps[k].activePixmaps = creeps[k].defUnit->death_down_right;
                }
//                qDebug() << "tmpCreep->animationMaxIter: " << tmpCreep << "->" << tmpCreep->animationMaxIter;
                creeps[k].pixmap = creeps[k].activePixmaps[0];
                // ЛАЖА !!!!!!

                creep = &creeps[k];
                return true;
            }
            else
                creeps[k].hp = localHP;

            break;
        }
    }
    return false;
}

Creep* Creeps::getCreep(int number)
{
    return &creeps[number];
}

Creep* Creeps::getCreep(int x, int y)
{
    for(int k = 0; k < amount; k++)
    {
        int localX = creeps[k].coorByCellX;
        int localY = creeps[k].coorByCellY;

        if(localX == x && localY == y)
        {
            return &creeps[k];
        }
    }
    return NULL;
}

Creep* Creeps::createCreep(int coorByCellX, int coorByCellY, int coorByMapX, int coorByMapY, DefaultUnit* unit)
{
//    if(amount == size)
//    {
//        Creep* tmpCreeps;
//        tmpCreeps = new Creep[size+1];

//        for(int k = 0; k < size; k++)
//            tmpCreeps[k] = creeps[k];

//        size++;

//        delete[] creeps;
//        creeps = tmpCreeps;
//    }

    if(amount < size)
    {
        creeps[amount].hp = 100;
        creeps[amount].alive = true;
        creeps[amount].preDeath = false;
        creeps[amount].number = amount+1;
        creeps[amount].coorByCellX = coorByCellX;
        creeps[amount].coorByCellY = coorByCellY;
        creeps[amount].coorByMapX = coorByMapX;
        creeps[amount].coorByMapY = coorByMapY;
        creeps[amount].lastX = coorByCellX;
        creeps[amount].lastY = coorByCellY;

//        creeps[amount].speed = speed;
//        creeps[amount].type = type;

        creeps[amount].animationCurrIter = 0;
        creeps[amount].animationMaxIter = 0;

        creeps[amount].pixmap = defaultPixmapForCreep;
        creeps[amount].defUnit = unit;

        return &creeps[amount++];
    }

    return NULL;
}

void Creeps::setDefaulPixmapForCreep(QPixmap pixmap)
{
    defaultPixmapForCreep = pixmap;
}

QPixmap Creeps::getCreepPixmap(int x, int y)
{
    for(int k = 0; k < amount; k++)
    {
        int localX = creeps[k].coorByCellX;
        int localY = creeps[k].coorByCellY;

        if(localX == x && localY == y)
        {
            return creeps[k].pixmap;
        }
    }
    return defaultPixmapForCreep;
}
