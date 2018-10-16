#ifndef DEFAULTUNIT_H
#define DEFAULTUNIT_H

#include <QPixmap>

/**
 * @brief The DefaultUnit class - класс, описывающий все реализации определенного типа Юнита.
 */
class DefaultUnit
{
public:
    QString name;
    int healtPoint;
    int type;
//    int speed;

    QPixmap pixmap;

    QPixmap idle_up;
    QPixmap idle_up_right;
    QPixmap idle_right;
    QPixmap idle_down_right;
    QPixmap idle_down;
    QPixmap idle_down_left;
    QPixmap idle_left;
    QPixmap idle_up_left;

    std::vector<QPixmap> walk_up;
    std::vector<QPixmap> walk_up_right;
    std::vector<QPixmap> walk_right;
    std::vector<QPixmap> walk_down_right;
    std::vector<QPixmap> walk_down;
    std::vector<QPixmap> walk_down_left;
    std::vector<QPixmap> walk_left;
    std::vector<QPixmap> walk_up_left;

    std::vector<QPixmap> attack_up;
    std::vector<QPixmap> attack_up_right;
    std::vector<QPixmap> attack_right;
    std::vector<QPixmap> attack_down_right;
    std::vector<QPixmap> attack_down;
    std::vector<QPixmap> attack_down_left;
    std::vector<QPixmap> attack_left;
    std::vector<QPixmap> attack_up_left;

    std::vector<QPixmap> death_up;
    std::vector<QPixmap> death_up_right;
    std::vector<QPixmap> death_right;
    std::vector<QPixmap> death_down_right;
    std::vector<QPixmap> death_down;
    std::vector<QPixmap> death_down_left;
    std::vector<QPixmap> death_left;
    std::vector<QPixmap> death_up_left;

    DefaultUnit();
    void clearVectors();
};

#endif // DEFAULTUNIT_H
