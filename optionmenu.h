#ifndef OPTIONMENU_H
#define OPTIONMENU_H

#include <QWidget>

namespace Ui {
class OptionMenu;
}

class OptionMenu : public QWidget
{
    Q_OBJECT

public:
    explicit OptionMenu(QWidget *parent = 0);
    ~OptionMenu();

private:
    Ui::OptionMenu *ui;

private slots:
    void on_returnButton_clicked();

signals:
    void signal_closeWidget();
};

#endif // OPTIONMENU_H
