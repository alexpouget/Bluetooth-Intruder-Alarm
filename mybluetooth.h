#ifndef MYBLUETOOTH_H
#define MYBLUETOOTH_H
#include "phone.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <QObject>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

class MyBluetooth : public QObject
{
    Q_OBJECT
public:
    MyBluetooth();
    void scan();
signals:
    void finishedScan(std::list<Phone*> phoneList);
    void finishedCheck(std::list<Phone*> phoneList);
public slots:
    void scanList();
    void checkAlert();

private:
    std::list<Phone*> phoneList;
};


#endif // MYBLUETOOTH_H
