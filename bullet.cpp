#include "bullet.h"

Bullet::Bullet() {
    flying = true;
//    bulletFly_TimerMilliSec = 100;
}

void Bullet::setSpeed(int speed) {
    this->speed = speed;
}

void Bullet::setCurrentCordinate(int currX, int currY) {
    this->currX = currX;
    this->currY = currY;
}

//void Bullet::setDestinationCordinate(int destX, int destY) {
//    this->destX = destX;
//    this->destY = destY;
//}
void Bullet::setCreep(Creep* creep) {
    this->creep = creep;
}

void Bullet::setPixmap(QPixmap pixmap) {
    this->pixmap = pixmap;
}

int Bullet::getSpeed() {
    return speed;
}

int Bullet::getCurrX() {
    return currX;
}

int Bullet::getCurrY() {
    return currY;
}

int Bullet::getDestinationX() {
    return destX;
}

int Bullet::getDestinationY() {
    return destY;
}

QPixmap Bullet::getPixmap() {
    return pixmap;
}

void Bullet::move() {
    int destX = creep->coorByMapX;
    int destY = creep->coorByMapY;

    if(currX != destX || currY != destY) {
        if(currX == destX) {
            if(currY < destY) {
                currY += speed;
            } else if (currY > destY) {
                currY -= speed;
            }
        } else if(currY == destY) {
            if(currX < destX) {
                currX += speed;
            } else if(currX > destX) {
                currX -= speed;
            }
        } else if(currX < destX && currY > destY) {
            currX += speed/2;
            currY -= speed/2;
        } else if(currX > destX && currY > destY) {
            currX -= speed/2;
            currY -= speed/2;
        } else if(currX < destX && currY < destY) {
            currX += speed/2;
            currY += speed/2;
        } else if(currX > destX && currY < destY) {
            currX -= speed/2;
            currY += speed/2;
        }
//        return true;
    } else {
        flying = false;
    }
//    return false;
}
