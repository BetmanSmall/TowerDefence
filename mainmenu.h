#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>

namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();
//    void paintEvent(QPaintEvent *);

private:
    Ui::MainMenu *ui;

private slots:
    void on_playButton_clicked();
    void on_optionsButton_clicked();
    void on_exitButton_clicked();

signals:
    void signal_openChooseMapMenu();
    void signal_openOptionMenu();
    void signal_exit();
};

#endif // MAINMENU_H
