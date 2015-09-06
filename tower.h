#ifndef TOWER_H
#define TOWER_H

#include <QPixmap>

#include "defaulttower.h"
#include "creep.h"
#include "bullet.h"

using namespace std;
/**
 * @brief The Tower class - класс, описывающий общие характеристики башни.
 */
class Tower
{
//private:
public:
    QString name;
    int attack;
    int radius;
    int size;
    int type;

    int currX, currY;
    int attackX, attackY;

    QPixmap pixmap;

    DefaultTower* defTower;

    vector<Bullet> bullets;

    Tower();

//    void createBulletAndShot(int attackX, int attackY);
    void createBulletAndShot(Creep* creep, int bullet_grafCoorX, int bullet_grafCoorY);

//    Tower(int type, int radius, int attack, QPixmap pixmap);
};

#endif // TOWER_H
