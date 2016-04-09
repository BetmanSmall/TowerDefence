#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

//#include <iostream>
//#include <fstream>
#include <time.h>

#include <QDebug>
#include <QWidget>
//#include <QGLWidget>
//#include <QOpenGLWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QString>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QXmlStreamReader>
#include <QBitmap>

#include "field.h"
#include "faction.h"
#include "underconstruction.h"

using namespace std;

namespace Ui {
    class GameWidget;
}

/**
 * @brief Данная структура отвечает за набор Tilов
 */
struct TileSet
{
    int firstTileID; /// jdfklsdjfsdjf
    QString name;
    int spacing;
    int margin;
    int tileWidth;
    int tileHeight;
    QPixmap img;
    vector< QRect > subRects;
};

/**
 * @brief Класс отвечает за игровую сессию
 * Вся игра проходит, полностью в этом классе
 */
class GameWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор GameWidget
     * @param parent - родительский QWidget
     */
    explicit GameWidget(QWidget *parent = 0);
    ~GameWidget();
    /**
     * @brief Обработчик всех таймеров
     * @param Евент таймера
     */
    void timerEvent(QTimerEvent* event);
    /**
     * @brief Обработчик нажатия клавиш на клавиатуре
     * @param Евент нажатия клавиши
     */
    void keyPressEvent(QKeyEvent* event);

    QPainter p;
    void paintEvent(QPaintEvent *);
    void drawGrid();
    void drawField();
    void drawFullField();
    void drawRelief();
    void drawTowersByField();
    void drawTowersByTowers();
    void drawCreeps();
    void drawStepsAndMouse();
    void drawTowersUnderConstruction();
    void drawTowerUnderConstruction(int buildX, int buildY, DefaultTower* tower);

    /**
     * @brief Переводит графические координаты в игровые
     * @param mouseX
     * @param mouseY
     * @return False - не смогли перевести. Возможно за пределами игрового поля.
     */
    bool whichCell(int &mouseX, int &mouseY);

    void startTimer_CreepsMoveAndTowerAttack();
    void stopTimer_CreepsMoveAndTowerAttack();

    void buildTower(int x = -1, int y = -1);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

//    void mouseReleaseEvent(QMouseEvent* event);
//    void mouseMoveEvent(QMouseEvent* event);
//    void leaveEvent(QEvent* event);

    /**
     * @brief Загрузка карты
     * @param mapName
     */
    void loadMap(QString mapName);

    bool gameStart;
    bool gamePause;
    bool mapLoad;

//    bool setUpBuildTower;

    UnderConstruction* underConstruction;
//    DefaultTower* towersUnderConstruction;
//    int towersStartUnderConstructionX, towersStartUnderConstructionY;

    int pixelsShiftMap;

    int zoomSizeCell;
    int zoomMaxSizeCell;
    int zoomMinSizeCell;

    int defaultNumCreateCreeps;

//    Timers
    int creepsMove_TimerMilliSec;
    int towersAttack_TimerMilliSec;
    int scanMouseMove_TimerMilliSec;
    int bulletsFly_TimerMilliSec;

    int bulletsFly_TimerId;
    int creepsMove_TimerId;
    int towersAttack_TimerId;
    int scanMouseMove_TimerId;

    int test;

    Field field;
    Faction faction;

//    Test Zone!
    QPixmap global_pixmap;
    string global_text;
    string global_text2;

private:
    Ui::GameWidget *ui;

    QString TOWER_DEFENCE_PATH;

private slots:
    void on_loadMaps_clicked();

    void on_clearMap_clicked();

    void on_closeWidget_clicked();

    void on_goCreeps_clicked();

signals:
    void signal_closeWidget();
};

#endif // GAMEWIDGET_H
