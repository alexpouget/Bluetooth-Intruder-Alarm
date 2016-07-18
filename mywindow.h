#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QFont>
#include <QPushButton>
#include <QWidget>
#include <QListView>
#include <QListWidget>
#include <QStringListModel>
#include <QStringList>
#include <QPainter>
#include <QLabel>
#include <QMessageBox>
#include <QInputDialog>
#include <QLineEdit>
#include <iostream>
#include <string>
#include <fstream>
#include "detector.h"
#include "phone.h"
#include "mybluetooth.h"
#include "sirene.h"
#include "mysirenethread.h"
#include <list>

class MyWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MyWindow(QWidget *parent = 0);
    bool verifCode(QString code);
    void setActive(bool _active);
    bool getActive();
    void alarm(bool flag);

signals:
    void updateScan();
private slots:
    void scan();
    void active();
    void add();
    void del();
    void checkAlert(std::list<Phone*> phoneList);
    void setList(std::list<Phone*> phoneList);
    void setCode();
private:
    QListWidget *listAll;
    QLabel *label;
    QLabel *lPeriph;
    QPushButton *activeButton;
    QPushButton *scanButton;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *codeButton;
    QListWidget *listPeriph;
    bool activeAlarm;
    MySireneThread sireneThread;
    Sirene *sirene;

protected:
    void paintEvent(QPaintEvent *e);
};

#endif // MYWINDOW_H
