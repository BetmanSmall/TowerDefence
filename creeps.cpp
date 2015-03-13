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
        int localX = creeps[k].currX;
        int localY = creeps[k].currY;

        if(localX == x && localY == y)
            return creeps[k].hp;
    }
    return 0;
}

bool Creeps::attackCreep(int x, int y, int hp, Creep *creep)
{
    for(int k = 0; k < amount; k++)
    {
        if(!creeps[k].alive)
            continue;

        int localX = creeps[k].currX;
        int localY = creeps[k].currY;

        if(localX == x && localY == y)
        {
            int localHP = creeps[k].hp;
            localHP = localHP - hp;

            if(localHP <= 0)
            {
                creeps[k].hp = 0;
                creeps[k].currX = -1;
                creeps[k].currY = -1;
                creeps[k].alive = false;
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
        int localX = creeps[k].currX;
        int localY = creeps[k].currY;

        if(localX == x && localY == y)
        {
            return &creeps[k];
        }
    }
    return NULL;
}

Creep* Creeps::createCreep(int x, int y, DefaultUnit* unit)
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
        creeps[amount].currX = x;
        creeps[amount].currY = y;
        creeps[amount].number = amount+1;
//        creeps[amount].type = type;
        creeps[amount].hp = 100;
        creeps[amount].alive = true;
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
        int localX = creeps[k].currX;
        int localY = creeps[k].currY;

        if(localX == x && localY == y)
        {
            return creeps[k].pixmap;
        }
    }
    return defaultPixmapForCreep;
}
