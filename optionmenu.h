#ifndef OPTIONMENU_H
#define OPTIONMENU_H

#include <QWidget>
//#include <QGLWidget>
//#include <QOpenGLWidget>
#include <QMediaPlayer>

namespace Ui {
class OptionMenu;
}

class OptionMenu : public QWidget
{
    Q_OBJECT

public:
    explicit OptionMenu(QWidget *parent = 0);
    ~OptionMenu();

    void setMediaPlayer(QMediaPlayer* mediaPlayer);

private:
    Ui::OptionMenu *ui;

    QMediaPlayer* mediaPlayer;

private slots:
    void on_returnButton_clicked();

    void on_Sound_sliderMoved(int position);

signals:
    void signal_closeWidget();
};

#endif // OPTIONMENU_H
