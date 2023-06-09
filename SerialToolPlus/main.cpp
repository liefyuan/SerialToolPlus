#include "mainwindow.h"

#include <QApplication>

/*
 * author:away
 * time: 2022-08-20
 * version2.0
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
