#include "underconstruction.h"

UnderConstruction::UnderConstruction() {
    this->isStartSet = false;
}

UnderConstruction::UnderConstruction(DefaultTower *tower) {
    this->isStartSet = false;
    this->tower = tower;
}

UnderConstruction::UnderConstruction(int startX, int startY, DefaultTower *tower) {
    this->isStartSet = true;
    this->startX = startX;
    this->startY = startY;
    this->tower = tower;
}

bool UnderConstruction::setStartCoors(int startX, int startY) {
    qDebug() << "UnderConstruction::setStartCoors(" << startX << "," << startY << ");";
    this->isStartSet = true;
    this->startX = startX;
    this->startY = startY;
}

bool UnderConstruction::setEndCoors(int endX, int endY) {
    qDebug() << "UnderConstruction::setEndCoors(" << endX << "," << endY << ");";
    this->endX = endX;
    this->endY = endY;

    if(tower != NULL) {
        coorsX.clear();
        coorsY.clear();
        if(endY == startY || (endY < (startY+tower->size) && endY > startY)) {
            if(endX >= startX) {
                for(int currX = startX+tower->size; currX <= endX; currX+=tower->size) {
                    this->coorsX.push_back(currX);
                    this->coorsY.push_back(startY);
                }
            } else {
                for(int currX = startX-tower->size; currX > endX-tower->size; currX-=tower->size) {
                    this->coorsX.push_back(currX);
                    this->coorsY.push_back(startY);
                }
            }
        } else if(endX == startX || endX < (startX+tower->size) && endX > startX) {
            if(endY >= startY) {
                for(int currY = startY+tower->size; currY <= endY; currY+=tower->size) {
                    this->coorsX.push_back(startX);
                    this->coorsY.push_back(currY);
                }
            } else {
                for(int currY = startY-tower->size; currY > endY-tower->size; currY-=tower->size) {
                    this->coorsX.push_back(startX);
                    this->coorsY.push_back(currY);
                }
            }
        }
        return true;
    }
    return false;
}

