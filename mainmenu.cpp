#include "mainmenu.h"
#include "ui_mainmenu.h"

#include <QDebug>
//#include <QPainter>

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    TOWER_DEFENCE_PATH = "../../TowerDefence/";
    ui->setupUi(this);

    ui->playButton->setIcon(QIcon(TOWER_DEFENCE_PATH + "images/Play.png"));
    ui->optionsButton->setIcon(QIcon(TOWER_DEFENCE_PATH + "images/Options.png"));
    ui->exitButton->setIcon(QIcon(TOWER_DEFENCE_PATH + "images/Exit.png"));

//    qDebug() << "MainMenu: X: " << width() << " Y: " << height();
}

MainMenu::~MainMenu()
{
    delete ui;
}

//void MainMenu::paintEvent(QPaintEvent *)
//{
//    QPainter p(this);
//    p.fillRect(0, 0, width(), height(), QColor(255, 0, 0));
//}

void MainMenu::on_playButton_clicked()
{
    qDebug() << "on_PlayButton_clicked()";
    signal_openChooseMapMenu();
}

void MainMenu::on_optionsButton_clicked()
{
    qDebug() << "on_OptionsButton_clicked()";
    signal_openOptionMenu();
}

void MainMenu::on_exitButton_clicked()
{
    qDebug() << "on_ExitButton_clicked";
    signal_exit();
}
