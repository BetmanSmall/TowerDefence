#ifndef DEFAULTTOWER_H
#define DEFAULTTOWER_H

#include <QPixmap>

/**
 * @brief The DefaultTower class - класс, описывающий все реализации определенного типа Башни.
 */
class DefaultTower
{
public:
    QString name;
    int attack;
    int radius;
    int size;
    int height;
    int type;

    QPixmap pixmap;

    QPixmap bullet_fly_up;
    QPixmap bullet_fly_up_right;
    QPixmap bullet_fly_right;
    QPixmap bullet_fly_down_right;
    QPixmap bullet_fly_down;
    QPixmap bullet_fly_down_left;
    QPixmap bullet_fly_left;
    QPixmap bullet_fly_up_left;

//    QPixmap idle_up;
//    QPixmap idle_up_right;
//    QPixmap idle_right;
//    QPixmap idle_down_right;
//    QPixmap idle_down;
//    QPixmap idle_down_left;
//    QPixmap idle_left;
//    QPixmap idle_up_left;

//    std::vector<QPixmap> attack_up;
//    std::vector<QPixmap> attack_up_right;
//    std::vector<QPixmap> attack_right;
//    std::vector<QPixmap> attack_down_right;
//    std::vector<QPixmap> attack_down;
//    std::vector<QPixmap> attack_down_left;
//    std::vector<QPixmap> attack_left;
//    std::vector<QPixmap> attack_up_left;

    DefaultTower();
};

#endif // DEFAULTTOWER_H
