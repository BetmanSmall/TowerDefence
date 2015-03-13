#ifndef WIDGET_H
#define WIDGET_H

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
//#include <QMessageBox>
#include <QXmlStreamReader>

#include <field.h>

using namespace std;

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent * event);

    QPainter p;
    void paintEvent(QPaintEvent *);
    void drawGrid();
    void drawField();
    void drawRelief();
    void drawTowers();
    void drawCreeps();
    void drawStepsAndMouse();

    bool whichCell(int *mouseX, int *mouseY);
    void startCreepTimer();
    void mousePressEvent( QMouseEvent * event );
//    void mouseReleaseEvent( QMouseEvent * event );

    bool gameStart;
    bool gamePause;
    bool mapLoad;

    int spaceWidget;
    int sizeCell;
    int tileWidth, tileHeight;

    int defaultNumCreateCreeps;
    int millisecForTimer;
    int creepsMoveTimerId;

    int test;

    Field field;

//    Test Zone!
    QPixmap global_pixmap;
    string global_text;
    string global_text2;

private slots:
    void on_loadMaps_clicked();

    void on_clearMap_clicked();

    void on_saveMaps_clicked();

    void on_goCreeps_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
