#ifndef WIDGETCONTROLLER_H
#define WIDGETCONTROLLER_H

#include <QWidget>
//#include <QGLWidget>
//#include <QOpenGLWidget>
#include <QMediaPlayer>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QPaintEvent>

#include "mainmenu.h"
#include "choosemapmenu.h"
#include "optionmenu.h"
#include "gamewidget.h"

class WidgetController : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetController(QWidget *parent = 0);

private:
    QMediaPlayer* mediaPlayer;
    QStackedWidget* stackedWidget;

    void paintEvent(QPaintEvent* );

    void loadMap(GameWidget *gameWidget);

    QString TOWER_DEFENCE_PATH;

private slots:
    void showMainMenu();

    void showChooseMapMenu();
    void showOptionMenu();

    void loadMap1();
    void loadMap2();
    void loadMap3();
    void loadMap4();
    void loadMap5();
    void loadMap6();
    void closeWidget();
};

#endif // WIDGETCONTROLLER_H
