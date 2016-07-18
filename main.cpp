#include <mywindow.h>
#include <mybluetooth.h>
#include <iostream>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyWindow window;
    window.showMaximized();

    QThread thread;
    Detector *detector = new Detector();
    detector->moveToThread(&thread);
    detector->connect(&thread,SIGNAL(started()),SLOT(work()));


    QThread thread2;
    MyBluetooth *bt = new MyBluetooth();
    bt->moveToThread(&thread2);
    bt->connect(&thread2,SIGNAL(started()),SLOT(scanList()));
    bt->connect(&window,SIGNAL(updateScan()),SLOT(scanList()));
    bt->connect(detector,SIGNAL(detected()),SLOT(checkAlert()));

    //typedef std::list<Phone> listPhone;
    qRegisterMetaType<std::list<Phone*> >("List<Phone>");
    window.connect(bt,SIGNAL(finishedScan(std::list<Phone*>)),SLOT(setList(std::list<Phone*>)));
    window.connect(bt,SIGNAL(finishedCheck(std::list<Phone*>)),SLOT(checkAlert(std::list<Phone*>)));

    thread.start();
    thread2.start();

    return a.exec();
}

