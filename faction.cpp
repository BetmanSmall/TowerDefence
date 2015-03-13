#include "faction.h"

Faction::Faction()
{
}

void Faction::creatyNewTower(int type, int radius, int attack, QPixmap pixmap)
{
    Tower tower(type, radius, attack, pixmap);

    towers.push_back(tower);
}

void Faction::creatyNewUnit(DefaultUnit unit)
{
    DefaultUnit tmp_unit = unit; // problem with memory
    units.push_back(tmp_unit);
}

vector<Tower> Faction::getFirstTowers()
{
    vector<Tower> exitTowers;

    exitTowers = towers;

//    for(int k = 0; k < towers.size(); k++)

    return exitTowers;
}

DefaultUnit* Faction::getDefaultUnitById(int id)
{
    return &units[id];
}
