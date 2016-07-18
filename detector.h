#ifndef DETECTOR_H
#define DETECTOR_H
#include <QApplication>
#include <QtCore>
#include <iostream>
#include "wiringPi.h"
#include <QObject>

class Detector : public QObject
{
    Q_OBJECT
public:
    Detector();

signals:
    void detected();
public slots:
    void work();
private:
    int value;
};

#endif // DETECTOR_H
