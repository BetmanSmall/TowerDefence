#ifndef CHOOSEMAPMENU_H
#define CHOOSEMAPMENU_H

#include <QWidget>
//#include <QGLWidget>
//#include <QOpenGLWidget>

namespace Ui {
class ChooseMapMenu;
}

class ChooseMapMenu : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseMapMenu(QWidget *parent = 0);
    ~ChooseMapMenu();

private:
    Ui::ChooseMapMenu *ui;

    QString TOWER_DEFENCE_PATH;

private slots:
    void on_returnButton_clicked();

    void on_loadMap1Button_clicked();
    void on_loadMap2Button_clicked();
    void on_loadMap3Button_clicked();

signals:
    void signal_closeWidget();
    void signal_loadMap1();
    void signal_loadMap2();
    void signal_loadMap3();
};

#endif // CHOOSEMAPMENU_H
