#include "choosemapmenu.h"
#include "ui_choosemapmenu.h"

#include <QDebug>

ChooseMapMenu::ChooseMapMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseMapMenu)
{
    ui->setupUi(this);

#ifdef QT_DEBUG
    TOWER_DEFENCE_PATH = "../../TowerDefence/";
#else
    TOWER_DEFENCE_PATH = "./";
#endif

    ui->loadMap1Button->setIcon(QIcon(TOWER_DEFENCE_PATH + "images/button1v2.png"));
    ui->loadMap2Button->setIcon(QIcon(TOWER_DEFENCE_PATH + "images/button2v2.png"));
    ui->loadMap3Button->setIcon(QIcon(TOWER_DEFENCE_PATH + "images/button3v2.png"));

//    qDebug() << "ChooseMapMenu: X: " << width() << " Y: " << height();
}

ChooseMapMenu::~ChooseMapMenu()
{
    delete ui;
}

void ChooseMapMenu::on_returnButton_clicked()
{
    signal_closeWidget();
}

void ChooseMapMenu::on_loadMap1Button_clicked()
{
    signal_loadMap1();
}

void ChooseMapMenu::on_loadMap2Button_clicked()
{
    signal_loadMap2();
}

void ChooseMapMenu::on_loadMap3Button_clicked()
{
    signal_loadMap3();
}

void ChooseMapMenu::on_loadMap4Button_clicked()
{
    signal_loadMap4();
}
