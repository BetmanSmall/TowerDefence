#include "widgetcontroller.h"

#include <QDebug>

WidgetController::WidgetController(QWidget *parent) :
    QWidget(parent)
{
    TOWER_DEFENCE_PATH = "../../TowerDefence/";
//    this->setMaximumWidth(640);
//    this->setMaximumHeight(480);
//    this->setMinimumWidth(640);
//    this->setMinimumHeight(480);

//    this->setWindowTitle("xyu");
//    QPalette palette;
//    palette.setBrush(this->backgroundRole(), QBrush(QImage(TOWER_DEFENCE_PATH + "images/mainmenu.jpg")));
//    palette.setBrush(this->backgroundRole(), QBrush(QColor(0, 0, 0)));
//    this->setPalette(palette);

//    qDebug() << "WidgetController: X: " << width() << " Y: " << height();

    stackedWidget = new QStackedWidget;

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->addWidget(stackedWidget);
    setLayout(layout);
//    show();
//    move(100,100);

    setWindowState(Qt::WindowFullScreen);

    showMainMenu();
}

void WidgetController::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    p.drawPixmap(0, 0, width(), height(), QPixmap(TOWER_DEFENCE_PATH + "images/mainmenu.jpg"));
}

void WidgetController::showMainMenu()
{
    qDebug() << "showMainMenu()";

    MainMenu* mainMenu = new MainMenu();

    connect(mainMenu, SIGNAL(signal_openChooseMapMenu()), this, SLOT(showChooseMapMenu()));
    connect(mainMenu, SIGNAL(signal_openOptionMenu()), this, SLOT(showOptionMenu()));
    connect(mainMenu, SIGNAL(signal_exit()), this, SLOT(closeWidget()));

    stackedWidget->addWidget(mainMenu);
    stackedWidget->setCurrentWidget(mainMenu);
}

void WidgetController::showChooseMapMenu()
{
    qDebug() << "showChooseMapMenu()";

    ChooseMapMenu* chooseMapMenu = new ChooseMapMenu();

    connect(chooseMapMenu, SIGNAL(signal_loadMap1()), this, SLOT(loadMap1()));
    connect(chooseMapMenu, SIGNAL(signal_loadMap2()), this, SLOT(loadMap2()));
    connect(chooseMapMenu, SIGNAL(signal_loadMap3()), this, SLOT(loadMap3()));
    connect(chooseMapMenu, SIGNAL(signal_closeWidget()), this, SLOT(closeWidget()));

    stackedWidget->addWidget(chooseMapMenu);
    stackedWidget->setCurrentWidget(chooseMapMenu);
}

void WidgetController::showOptionMenu()
{
    qDebug() << "showOptionMenu()";

    OptionMenu* optionMenu = new OptionMenu();

    connect(optionMenu, SIGNAL(signal_closeWidget()), this, SLOT(closeWidget()));

    stackedWidget->addWidget(optionMenu);
    stackedWidget->setCurrentWidget(optionMenu);
}

void WidgetController::loadMap(GameWidget* gameWidget)
{
    qDebug() << "loadMap()";

    connect(gameWidget, SIGNAL(signal_closeWidget()), this, SLOT(closeWidget()));

    stackedWidget->addWidget(gameWidget);
    stackedWidget->setCurrentWidget(gameWidget);
}

void WidgetController::loadMap1()
{
    qDebug() << "loadMap1()";

    GameWidget* gameWidget = new GameWidget();

    loadMap(gameWidget);

    gameWidget->loadMap(TOWER_DEFENCE_PATH + "maps/arctic.tmx");
}


void WidgetController::loadMap2()
{
    qDebug() << "loadMap2()";

    GameWidget* gameWidget = new GameWidget();

    loadMap(gameWidget);

    gameWidget->loadMap(TOWER_DEFENCE_PATH + "maps/forest.tmx");
}

void WidgetController::loadMap3()
{
    qDebug() << "loadMap3()";

    GameWidget* gameWidget = new GameWidget();

    loadMap(gameWidget);

    gameWidget->loadMap(TOWER_DEFENCE_PATH + "maps/desert.tmx");
}

void WidgetController::closeWidget()
{
    qDebug() << "close";

    QWidget* currentWidget = stackedWidget->currentWidget();

    if(stackedWidget->currentIndex() == 0)
        this->close();
    else// if((stackedWidget->currentWidget() == w) && (stackedWidget->currentIndex() != 0))
    {
        stackedWidget->setCurrentIndex(stackedWidget->count() - 2);
        stackedWidget->removeWidget(currentWidget);
        disconnect(currentWidget);
        delete currentWidget;
    }
}
