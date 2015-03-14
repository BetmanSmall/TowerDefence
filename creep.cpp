#include "creep.h"

Creep::Creep()
{
}

QPixmap Creep::getAnimationInformation(int *lastX, int *lastY, int *animationCurrIter, int *animationMaxIter)
{
    *lastX = this->lastX;
    *lastY = this->lastY;
    *animationCurrIter = this->animationCurrIter;
    *animationMaxIter = this->animationMaxIter;

    return this->pixmap;
}
