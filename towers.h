#ifndef TOWERS_H
#define TOWERS_H

#include <stdlib.h>

#include <QDebug>
#include <QPixmap>

#include "tower.h"

using namespace std;

//class Tower
//{
//public:
//    int type;
//    int radius;
//    int attack;
//    int currX, currY;
//    QPixmap pixmap;
//};

/**
 * @brief The Towers class
 */
class Towers
{
    Tower* towers;

    QPixmap defaultPixmapForTower;

    /**
     * @brief size - Количество башен, которое может быть создано;
     * максимально возможное и ограниченное данным параметром.
     */
    int size;
    /**
     * @brief amount - Количество созданных башен
     */
    int amount;

public:
    /**
     * @brief Конструктор. Массив башен инициилизируется NULL, чтобы определить, что массив нужно создать.
     * Нужно определять создан ли массив башен или нет, чтобы не возникло проблем при игровой инициализации массива.
     */
    Towers():towers(NULL) {}

    /**
     * @brief Деструктор. Вызывает функцию deleteField(). Она в свою очередь очищает память из под массива башен.
     *
     */
    ~Towers() {deleteField();}

    /**
     * @brief createField - инициализирует массив башен
     * @param size - максимально возможное количество башен
     */
    void createField(int size);
    /**
     * @brief deleteField - удаляет массив башен
     */
    void deleteField();

    /**
     * @brief getSize - возвращает максимальное количество башен, которое может быть
     * @return
     */
    int getSize();
    /**
     * @brief getAmount - возвращает количество созданных башен
     * @return
     */
    int getAmount();

    /**
     * @brief getTowerById - возвращает башню по её ID в массиве
     * @param number - параметр ID
     * @return - возвращает указатель на нужную башню
     */
    Tower* getTowerById(int number);
    /**
     * @brief getTower - ищет и возвращает башню по координатам. Если x = -1; y = -1,
     * то параметры в функцию не передались, будет возвращена последняя созданная башня по ID
     * @param x - координаты по оси x
     * @param y - координаты по оси y
     * @return - возвращает указатель на башню или NULL, если переданные координаты не совпали
     * с координатами ни одной башни в массиве.
     */
    Tower* getTower(int x = -1, int y = -1);

    /**
     * @brief устарела
     */
    Tower* createTower(int x, int y, int type = 0);
    /**
     * @brief createTower - Если переменная size позволяет создать ещё башню, то инициализирует новую башню:
     * определяем координаты местонахождения, размер атаки, радиус, тип.
     * @param x - координаты, где нужно создать башню по оси x
     * @param y - координаты, где нужно создать башню по оси y
     * @param tower - реализация башни по-умолчанию (уровень модификации, тип, и т. д.)
     * @return - возвращает указатель на созданную башню [и увеличивает количесвто созданных башен на 1].
     */
    Tower* createTower(int x, int y, DefaultTower* tower);
    /**
     * @brief deleteTower - удаляет башню по координатам. Если x = -1; y = -1,
     * то параметры в функцию не передались, приравниваем x и y к координатам предыдущей созданной башни,
     * и уменьшаем количество созданных башен на 1.
     * @param x - координаты по оси x
     * @param y - координаты по оси y
     * @return false, если координаты не совпали ни с одной башней; true - удалили успешно
     */
    bool deleteTower(int &x, int &y);

    /**
     * @brief setDefaulPixmapForTower - устанавливает картинку башни по-умолчанию
     * @param pixmap - картинка
     */
    void setDefaulPixmapForTower(QPixmap pixmap);
    /**
     * @brief getTowerPixmap - возвращает картинку башни с переданными координатами. Идёт поиск по всем
     * созданным башням
     * @param x - координаты по оси x
     * @param y - координаты по оси у
     * @return - возвращает картинку башни, находящуюся по данным координатам
     */
    QPixmap getTowerPixmap(int x, int y);
};

#endif // TOWERS_H
