#ifndef FACTION_H
#define FACTION_H

#include "tower.h"
#include "defaultunit.h"

using namespace std;

class Faction
{
    vector<Tower> towers;
    vector<DefaultUnit> units;
public:
    Faction();

    void creatyNewTower(int type, int radius, int attack, QPixmap pixmap);
    void creatyNewUnit(DefaultUnit unit);

    vector<Tower> getFirstTowers();
    DefaultUnit* getDefaultUnitById(int id);
};

#endif // FACTION_H
