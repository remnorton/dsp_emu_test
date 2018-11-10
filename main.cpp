/*
 * main.cpp
 *
 *  Created on: 29.10.2018
 *		Author: Rudenko Roman (aka Rem Norton)
 *
 */


#include<QDebug>
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
