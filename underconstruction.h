#ifndef UNDERCONSTRUCTION_H
#define UNDERCONSTRUCTION_H

#include "defaulttower.h"

class UnderConstruction
{
public:
    UnderConstruction();

    int startX, startY;
    int endX, endY;

    DefaultTower* tower;

    std::vector<int> coorsX;
    std::vector<int> coorsY;
};

#endif // UNDERCONSTRUCTION_H
