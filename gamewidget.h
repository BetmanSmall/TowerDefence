#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

//#include <iostream>
//#include <fstream>
#include <time.h>

#include <QDebug>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QString>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QXmlStreamReader>

#include "field.h"
#include "faction.h"

using namespace std;

namespace Ui {
    class GameWidget;
}

struct TileSet
{
    int firstTileID;
    QString name;
    int spacing;
    int margin;
    int tileWidth;
    int tileHeight;
    QPixmap img;
    vector< QRect > subRects;
};

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameWidget(QWidget *parent = 0);
    ~GameWidget();
    void timerEvent(QTimerEvent* event);
    void keyPressEvent(QKeyEvent* event);

    QPainter p;
    void paintEvent(QPaintEvent *);
    void drawGrid();
    void drawField();
    void drawRelief();
    void drawTowersByField();
    void drawTowersByTowers();
    void drawCreeps();
    void drawStepsAndMouse();
    void drawTowerUnderConstruction();

    bool whichCell(int *mouseX, int *mouseY);

    void startTimer_CreepsMoveAndTowerAttack();
    void stopTimer_CreepsMoveAndTowerAttack();

    void buildTower(int x = -1, int y = -1);
    void mousePressEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

//    void mouseReleaseEvent(QMouseEvent* event);
//    void mouseMoveEvent(QMouseEvent* event);
//    void leaveEvent(QEvent* event);

    void loadMap(QString mapName);

    bool gameStart;
    bool gamePause;
    bool mapLoad;

//    bool setUpBuildTower;
    DefaultTower* towerUnderConstruction;
    int towerUnderConstructionX, towerUnderConstructionY;

    int mainCoorMapX, mainCoorMapY;
    int pixelsShiftMap;
    int spaceWidget;
    int sizeCell;
    int zoomSizeCell;
    int zoomMaxSizeCell;
    int zoomMinSizeCell;

    int defaultNumCreateCreeps;

//    Timers
    int creepsMove_TimerMilliSec;
    int towersAttack_TimerMilliSec;
    int scanMouseMove_TimerMilliSec;

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

private slots:
    void on_loadMaps_clicked();

    void on_clearMap_clicked();

    void on_closeWidget_clicked();

    void on_goCreeps_clicked();

signals:
    void signal_closeWidget();
};

#endif // GAMEWIDGET_H
