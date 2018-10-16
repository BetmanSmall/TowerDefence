#include <QApplication>

#include "widgetcontroller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidgetController w;
    w.show();

    return a.exec();
}
