#include "tower.h"

Tower::Tower()
{
    this->attackX = -1;
    this->attackY = -1;
}

//void Tower::createBulletAndShot(int attackX, int attackY) {
void Tower::createBulletAndShot(Creep* creep, int bullet_grafCoorX, int bullet_grafCoorY) {
    Bullet bullet;

    bullet.setSpeed(10);
    bullet.setCurrentCordinate(bullet_grafCoorX, bullet_grafCoorY);
//    bullet.setDestinationCordinate(creep->currX, creep->currY);
    bullet.setCreep(creep);
    bullet.setPixmap(defTower->bullet_fly_up);

    bullets.push_back(bullet);
}

//Tower::Tower(int type, int radius, int attack, QPixmap pixmap)
//{
//    this->type = type;
//    this->radius = radius;
//    this->attack = attack;
//    this->pixmap = pixmap;
//}
