#include <QApplication>
#include "mainwidget.h"
#include "botspecification.h"
#include <QStackedWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWidget w;
    w.show();
    return a.exec();
}
