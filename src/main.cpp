/**
 * @file main.cpp
 * @brief Entry point of the program, creates the calculator window.
 */

#include "mainwindow.h"
#include <QApplication>

/// Entry point of the program
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
