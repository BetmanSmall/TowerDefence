#ifndef DEFAULTTOWER_H
#define DEFAULTTOWER_H

#include <QPixmap>

class DefaultTower
{
public:
    QString name;
    int attack;
    int radius;
    int size;
    int type;

    QPixmap pixmap;

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
