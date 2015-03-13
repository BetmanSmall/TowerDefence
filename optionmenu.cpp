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

void OptionMenu::on_returnButton_clicked()
{
    signal_closeWidget();
}
