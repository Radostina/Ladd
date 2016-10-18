#include "widget.h"
#include <QApplication>
#include <QDebug>
#include <iostream>
#include <QString>

#include "settingspage.h"
#include "controller/maincontroller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    unsigned char x = 0x0;
    x&=0x01;
    MainController mainController;
    mainController.init();
    QByteArray array("126");
    QString string("126");
    QString bitString = QString::number(string.toInt(), 2);
    qDebug() << bitString;
    return a.exec();
}
