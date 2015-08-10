#ifndef FIELD_H
#define FIELD_H

//#define CIRCLET8
#include <iostream>

#include <QPixmap>

#include "creeps.h"
#include "towers.h"
#include "faction.h"

/**
 * @brief Ячейка
 */
class Cell
{
public:
    Cell()
    {
        step = 0;
        empty = true;
        busy = false;
        spawn = false;
        exit = false;

//        tower = NULL;
        tower = false;
//        creeps = NULL;

//        pixmap = null;
//        busyPixmap = null;
    }

    int step;
    bool empty;
    bool busy;

    bool spawn; // NEED Check!!!!! ?????  Check
    bool exit; // NEED Check!!!!! ????? // NEED Check!!!!! ????? // NEED Check!!!!! ?????

//    Tower* tower;
    bool tower;
    vector<Creep*> creeps;

    QPixmap backgroundPixmap;
    QPixmap busyPixmap;
};

/**
 * @brief Поле из ячеек
 * @details Класс так же отвечает за Башни, Криппы. И пока что одну фракцию
 */
class Field
{
    Cell* field;
    Towers towers;
    Creeps creeps;
    Faction* faction1;

    bool creepSet;

    int gameOverLimitCreeps;
    int currentFinishedCreeps;

//    int sizeWidgetWidth;
//    int sizeWidgetHeight;

    int sizeX, sizeY;

    int mouseX, mouseY;
    int spawnPointX, spawnPointY;
    int exitPointX, exitPointY;

public:
    /**
     * @brief Конструктор. Сразу же в .h устанавливает указатель на массив из ячеек как NULL
     */
    Field():field(NULL) {}

    ~Field() {deleteField();}

    /**
     * @brief Создает поле, размерностью (newSizeX, newSizeY)
     * @param newSizeX
     * @param newSizeY
     */
    void createField(int newSizeX, int newSizeY);
    /**
     * @brief Очищает память из под поля
     */
    void deleteField();

    /**
     * @brief Временная функция, устанавливает Фракцию
     * @param Фракция
     */
    void setFaction(Faction* faction);

    /**
     * @brief Устанавливает точку спавна на поле
     * @param Колличество крипов, которые будут созданы из этой точки
     * @param Координаты по X
     * @param Координаты по Y
     * @return True - успешно; False - не получилось
     */
    bool createSpawnPoint(int num, int x = -1, int y = -1);
    /**
     * @brief Устанавливает точку куда криппы должны идти
     * @param Координаты по X
     * @param Координаты по Y
     */
    void createExitPoint(int x, int y);

    /**
     * @brief Возвращает размер поля по X
     * @return Число клеток по X
     */
    int getSizeX();
    /**
     * @brief Возвращает размер поля по Y
     * @return Число клеток по Y
     */
    int getSizeY();

    /**
     * @brief Функция которая заставляет атаковать все башни, когда в радиусе обзора есть крипп
     * @return Пока что всегда тру
     */
    bool towersAttack();
    /**
     * @brief Применяет Волновой Алгоритм на поле из ячееки по данным кординатам
     * @param Координаты по X
     * @param Координаты по Y
     */
    void waveAlgorithm(int x = -1, int y = -1);
    /**
     * @brief Рекурсивная функция для волнового алгоритма
     * @param Координаты по X
     * @param Координаты по Y
     * @param Число для данной ячейки
     */
    void waveStep(int x, int y, int step);

    /**
     * @brief setMousePress
     * @param x
     * @param y
     */
    void setMousePress(int x, int y);
    /**
     * @brief getMousePress
     * @param x
     * @param y
     * @return
     */
    bool getMousePress(int x = -1, int y = -1);
    /**
     * @brief Проверяет установленная ли Спавн точка
     * @param x
     * @param y
     * @return 1 - Созданная. 0 - не создана.
     */
    bool isSetSpawnPoint(int x = -1, int y = -1);
    /**
     * @brief Проверяет установленная ли точка выхода
     * @param x
     * @param y
     * @return 1 - Созданная. 0 - не создана.
     */
    bool isSetExitPoint(int x = -1, int y = -1);

    /**
     * @brief Говорит всем криппам ходить
     * @return 2 - все криппы мертвы
     * @return 1 - если колличество криппов в точке @exitPoint превышено @gameOverLimitCreeps
     * @return 0 - все криппы сходили успешно
     * @return -1 - какому-либо криппу перекрыли путь до @exitPoint
     */
    int stepAllCreeps();
    /**
     * @brief stepOneCreep
     * @param num
     * @return
     */
    int stepOneCreep(int num);

    /**
     * @brief Возращает номер шага для волнового алгоритма с проверками
     * @param x
     * @param y
     * @return Номер шага
     */
    int getNumStep(int x, int y);
    /**
     * @brief Возращает номер шага для волнового алгоритма без проверок
     * @param x
     * @param y
     * @return Номер шага
     */
    int getStepCell(int x, int y);
    /**
     * @brief Устнавливает номер шага в ячейки из расчета волнового алгоритма
     * @param x
     * @param y
     * @param Номер шага волнового алгоритма
     * @return True/False установли/не установил по определеным причинам
     */
    bool setNumOfCell(int x, int y, int step);
    /**
     * @brief Непосредственно устанавливает номер шага в ячейку
     * @param x
     * @param y
     * @param Номер шага волнового алгоритма
     */
    void setStepCell(int x, int y, int step);
    /**
     * @brief Сброс номер шага в ячейке
     * @param x
     * @param y
     */
    void clearStepCell(int x, int y);

    /**
     * @brief Возвращает указатель на объект класса "крипп" по полученным координатам
     * @param x
     * @param y
     * @return Указатель на объект класса "крипп"
     */
    Creep* getCreep(int x, int y);
    /**
     * @brief Возвращает вектор криппов, находящихся в этой ячейке
     * @param x
     * @param y
     * @return Вектор указателей на обекты криппов
     */
    std::vector<Creep *> getCreeps(int x, int y);
    /**
     * @brief Устарело
     * @param x
     * @param y
     * @return
     */
    int getCreepHpInCell(int x, int y);
    /**
     * @brief Возвращает указатель на криппа, с наименьшим хп в данной ячейке
     * @param x
     * @param y
     * @return Указатель на криппа
     */
    Creep* getCreepWithLowHP(int x, int y);

    /**
     * @brief Возвращает вектор указателей всех башен созданных в объекте класса @Towers
     * @return Вектор указателей на объекты башен
     */
    std::vector<Tower*> getAllTowers();

    /**
     * @brief Проверяет пустая ли ячейка
     * @param x
     * @param y
     * @return True/False свободна/занята
     */
    bool containEmpty(int x, int y);
    /**
     * @brief Проверяет занята ли клетка рельефом
     * @param x
     * @param y
     * @return True/False занята/свободна
     */
    bool containBusy(int x, int y);
    /**
     * @brief Проверяет занята ли клетка башней
     * @param x
     * @param y
     * @return True/False занята/свободна
     */
    bool containTower(int x, int y);
    /**
     * @brief Возвращает индекс криппа в данной клетке (с учетом того что в данной клектке могут находится несколько криппов)
     * @param x
     * @param y
     * @return 0 - Нет крипов, либо нет данного криппа.
     * @return {int} - индекс криппа, либо количество криппов
     */
    int containCreep(int x, int y, Creep* creep = NULL);

    /**
     * @brief Устанавливает занятость клетки и соответсвующую картинку
     * @param x
     * @param y
     * @param Картинка рельефа
     * @return True/False установил/не установил
     */
    bool setBusy(int x, int y, QPixmap pixmap);
    /**
     * @brief Устаревшая
     * @param x
     * @param y
     * @return
     */
    bool setTower(int x, int y);//, int type = 0);
    /**
     * @brief Устанавливает башню на основе Стандартной Башни из фракции
     * @param x
     * @param y
     * @param Стандартная башня
     * @return True/False установил/не установил
     */
    bool setTower(int x, int y, DefaultTower* defTower);
    /**
     * @brief Создать криппа в spawnPoint'e
     * @return True/False создал/не создал
     */
    bool setCreepInSpawnPoint();//Creep* creep = NULL);//, int type = 0);
    /**
     * @brief Устанавливает криппа в данную клетку
     * @param x
     * @param y
     * @param Крипп
     * @return True/False установил/не установил
     */
    bool setCreep(int x, int y, Creep* creep = NULL);//, int type = 0);

//    /**
    bool clearBusy(int x, int y);
//    /**
    bool clearTower(int x, int y);
//    /**
    bool clearCreep(int x, int y, Creep* creep = NULL);

//    /**
    bool deleteTower(int x = -1, int y = -1);

//    /**
    void setPixmapInCell(int x, int y, QPixmap pixmap);
//    /**
    void setPixmapForCreep(QPixmap pixmap);
//    /**
    void setPixmapForTower(QPixmap pixmap);
//    /**

//    /**
    QPixmap getBusyPixmapOfCell(int x, int y);
//    /**
    QPixmap getPixmapOfCell(int x, int y);
//    /**
    QPixmap getCreepPixmap(int x, int y);
//    /**
    QPixmap getTowerPixmap(int x, int y);
//    /**
};

#endif // FIELD_H
