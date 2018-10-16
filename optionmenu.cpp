#include "optionmenu.h"
#include "ui_optionmenu.h"

OptionMenu::OptionMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionMenu)
{
    ui->setupUi(this);
}

OptionMenu::~OptionMenu()
{
    delete ui;
}

void OptionMenu::setMediaPlayer(QMediaPlayer *mediaPlayer)
{
    this->mediaPlayer = mediaPlayer;
    qDebug() << "OptionMenu::setMediaPlayer() -- mediaPlayer->volume(): " << mediaPlayer->volume();
    ui->Sound->setValue(mediaPlayer->volume());
}

void OptionMenu::on_returnButton_clicked()
{
    signal_closeWidget();
}

void OptionMenu::on_Sound_sliderMoved(int position)
{
    qDebug() << "OptionMenu::on_Sound_sliderMoved() -- position: " << position;
    mediaPlayer->setVolume(position);
}
