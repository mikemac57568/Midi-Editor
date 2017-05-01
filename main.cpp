#include "mainwindow.h"
#include <QApplication>
#include <miditest.h>
#include <strummify.h>
#include <string>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    return a.exec();
}
