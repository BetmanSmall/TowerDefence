#ifndef FIELD_H
#define FIELD_H

#define CIRCLET8
#include <iostream>

#include <QPixmap>

#include "creeps.h"
#include "towers.h"
#include "faction.h"

class Cell
{
public:
    Cell()
    {
        step = 0;
        empty = true;
        busy = false;
        spawn = false;
        exit = false;

//        tower = NULL;
        tower = false;
//        creeps = NULL;

//        pixmap = null;
//        busyPixmap = null;
    }

    int step;
    bool empty;
    bool busy;

    bool spawn; // NEED Check!!!!! ?????  Check
    bool exit; // NEED Check!!!!! ????? // NEED Check!!!!! ????? // NEED Check!!!!! ?????

//    Tower* tower;
    bool tower;
    vector<Creep*> creeps;

    QPixmap backgroundPixmap;
    QPixmap busyPixmap;
};

class Field
{
    Cell *field;
    Towers towers;
    Creeps creeps;
    Faction* faction1;

    bool creepSet = true;

    int gameOverLimitCreeps;
    int currentFinishedCreeps;

//    int sizeWidgetWidth;
//    int sizeWidgetHeight;

    int sizeX, sizeY;

    int mouseX, mouseY;
    int spawnPointX, spawnPointY;
    int exitPointX, exitPointY;

public:
    Field():field(NULL) {}

    ~Field() {deleteField();}

    void createField(int newSizeX, int newSizeY);
    void deleteField();

    void setFaction(Faction* faction);

    bool createSpawnPoint(int num, int x = -1, int y = -1);
    void createExitPoint(int x, int y);

    int getSizeX();
    int getSizeY();

    bool towersAttack();
    void waveAlgorithm(int x = -1, int y = -1);
    void waveStep(int x, int y, int step);

    void setMousePress(int x, int y);
    bool getMousePress(int x = -1, int y = -1);
    bool isSetSpawnPoint(int x = -1, int y = -1);
    bool isSetExitPoint(int x = -1, int y = -1);

    int stepAllCreeps();
    int stepOneCreep(int num);

    int getNumStep(int x, int y);
    int getStepCell(int x, int y);
    bool setNumOfCell(int x, int y, int step);
    void setStepCell(int x, int y, int step);
    void clearStepCell(int x, int y);

    Creep* getCreep(int x, int y);
    std::vector<Creep *> getCreeps(int x, int y);
    int getCreepHpInCell(int x, int y);
//    std:vector<

    bool containEmpty(int x, int y);
    bool containBusy(int x, int y);
    bool containTower(int x, int y);
    int containCreep(int x, int y, Creep* creep = NULL);

    bool setBusy(int x, int y, QPixmap pixmap);
    bool setTower(int x, int y, int type = 0);
    bool setTower(int x, int y, DefaultTower* defTower);
    bool setCreep(int x = -1, int y = -1, Creep* creep = NULL);//, int type = 0);

    bool clearBusy(int x, int y);
    bool clearTower(int x, int y);
    bool clearCreep(int x, int y, Creep* creep = NULL);

    bool deleteTower(int x = -1, int y = -1);

    bool setPixmapInCell(int x, int y, QPixmap pixmap);
    bool setPixmapForCreep(QPixmap pixmap);
    bool setPixmapForTower(QPixmap pixmap);

    QPixmap getBusyPixmapOfCell(int x, int y);
    QPixmap getPixmapOfCell(int x, int y);
    QPixmap getCreepPixmap(int x, int y);
    QPixmap getTowerPixmap(int x, int y);
};

#endif // FIELD_H
