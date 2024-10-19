#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include "../Lib/supportfunctions.h"

int main(int argc, char *argv[])
{
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
}
