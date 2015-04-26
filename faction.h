#ifndef FACTION_H
#define FACTION_H

#include "tower.h"
#include "defaultunit.h"
#include "defaulttower.h"

using namespace std;

class Faction
{
    vector<DefaultTower> towers;
    vector<DefaultUnit> units;

public:
    Faction();

//    void creatyNewTower(int type, int radius, int attack, QPixmap pixmap);
    void creatyNewTower(DefaultTower tower);
    void creatyNewUnit(DefaultUnit unit);

    vector<DefaultTower*> getFirstTowers();
    DefaultUnit* getDefaultUnitById(int id);
};

#endif // FACTION_H
