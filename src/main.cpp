#include "mainwindow.h"

#include "core/filesWork/loadManagerCpp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();

    return app.exec();
}
