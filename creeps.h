#ifndef CREEPS_H
#define CREEPS_H

#include <stdlib.h>

#include <QPixmap>

//#include "defaultunit.h"
#include "creep.h"

//class Creep
//{
//public:
//    int type;
//    int number;
////    int speed;
//    int currX, currY;

//    int hp;
//    bool alive;
//    QPixmap pixmap;
//};

/**
 * @brief The Creeps class
 */
class Creeps
{
    Creep* creeps;

    QPixmap defaultPixmapForCreep;

    /**
     * @brief size - Количество крипов, которое может быть создано;
     * максимально возможное и ограниченное данным параметром.
     */
    int size;
    /**
     * @brief amount - Количество созданных крипов
     */
    int amount;

public:
    /**
     * @brief Creeps.  Конструктор. Массив крипов инициилизируется NULL, чтобы определить, что массив нужно создать.
     * Нужно определять создан ли массив крипов или нет, чтобы не возникло проблем при игровой инициализации массива
     */
    Creeps():creeps(NULL) {}

    /**
     * @brief  Деструктор. Вызывает функцию deleteMass(). Она в свою очередь очищает память из под массива крипов.
     */
    ~Creeps() {deleteMass();}

    /**
     * @brief createMass - иноциализирует массив крипов.
     * @param newSize - максимально возможное количество крипов.
     */
    void createMass(int newSize);
    /**
     * @brief deleteMass - удаляет массив крипов.
     */
    void deleteMass();

    /**
     * @brief getSize - возвращает максимальное количество крипов, которое может быть.
     * @return - количество крипов.
     */
    int getSize();
    /**
     * @brief getAmount - возвращает количество созданных крипов.
     * @return - количество крипов.
     */
    int getAmount();
    /**
     * @brief getHP - возвращает количество здоровья крипа, находящегося по заданным координатам.
     * @param x - координаты по оси x.
     * @param y - координаты по оси y.
     * @return
     */
    int getHP(int x, int y);

    /**
     * @brief attackCreep - наносит определенному (по переданным координатам) крипу урон, равный переменной @hp.
     * Если этот урон превышает текущее количество здоровья крипа, то убивает его. Также, в зависимости от направления ходьбы
     * крипа устанавливает определнённые иллюстрации смерти.
     * @param x - координаты по оси x.
     * @param y - координаты по оси y.
     * @param damage - урон, наносимый крипу.
     * @param creep - указатель на крипа.
     * @return - true, если нужный крип найден и урон нанесён; false - крип не найден, урон не нанесён.
     */
    bool attackCreep(int x, int y, int damage, Creep* creep);

    /**
     * @brief getCreep - возвращает крипа по его номеру в массиве
     * @param number - номер крипа в массиве
     * @return - возвращает указатель на нужного крипа.
     */
    Creep* getCreep(int number);
    /**
     * @brief getCreep - ищет и возвращает крипа по координатам. Если x = -1; y = -1,
     * то параметры в функцию не передались, будет возвращена последний созданный крип по ID.
     * @param x - координаты по оси x.
     * @param y - координаты по оси y.
     * @return - возвращает указатель на крипа или NULL, если переданные координаты не совпали
     * с координатами ни одного крипа в массиве.
     */
    Creep* getCreep(int x, int y);
    /**
     * @brief createCreep - Если переменная size позволяет создать ещё крипа, то инициализирует нового крипа.
     * @param coorByCellX - координаты, где нужно создать крипа по оси x << Trouble
     * @param coorByCellY - координаты, где нужно создать крипа по оси y << Trouble
     * @param coorByMapX - координаты, где нужно создать крипа по оси x << Trouble
     * @param coorByMapX - координаты, где нужно создать крипа по оси y << Trouble
     * @param unit - реализация крипа по-умолчанию (уровень модификации, тип, и т. д.)
     * @return - возвращает указатель на созданного крипа [и увеличивает количесвто созданных крипов на 1].
     */
    Creep* createCreep(int coorByCellX, int coorByCellY, int coorByMapX, int coorByMapY, DefaultUnit* unit);

    /**
     * @brief setDefaulPixmapForCreep - устанавливает картинку крипа по-умолчанию.
     * @param pixmap - картинка.
     */
    void setDefaulPixmapForCreep(QPixmap pixmap);
    /**
     * @brief getCreepPixmap - возвращает картинку крипа с переданными координатами. Идёт поиск по всем
     * созданным крипам.
     * @param x - координаты по оси x.
     * @param y - координаты по оси y.
     * @return - возвращат картинку крипа, находящегося по переданным координатам.
     */
    QPixmap getCreepPixmap(int x, int y);
};

#endif // CREEPS_H
