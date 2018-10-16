#include "faction.h"

#include <QDebug>

Faction::Faction()
{
}

//void Faction::creatyNewTower(int type, int radius, int attack, QPixmap pixmap)
//{
//    Tower tower(type, radius, attack, pixmap);

//    towers.push_back(tower);
//}

void Faction::creatyNewTower(DefaultTower tower)
{
    DefaultTower tmp_tower = tower; // problem with memory too......
    towers.push_back(tmp_tower);
}

void Faction::creatyNewUnit(DefaultUnit unit)
{
    DefaultUnit tmp_unit = unit; // problem with memory
    units.push_back(tmp_unit);
}

vector<DefaultTower *> Faction::getFirstTowers()
{
    vector<DefaultTower*> exitTowers;

//    exitTowers = towers;
    qDebug() << "towers.size(): " << towers.size();

    for(int k = 0; k < towers.size(); k++)
        exitTowers.push_back(&towers[k]);

    qDebug() << "exitTowers.size(): " << exitTowers.size();

    return exitTowers;
}

DefaultUnit* Faction::getDefaultUnitById(int id)
{
    return &units[id];
}
