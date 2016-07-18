#-------------------------------------------------
#
# Project created by QtCreator 2016-06-28T21:14:28
#
#-------------------------------------------------

QT       += core gui widgets multimedia

TARGET = alarm
TEMPLATE = app


LIBS += -L/usr/local/lib -lwiringPi -L/usr/include/bluetooth -lbluetooth

SOURCES += main.cpp \
    mywindow.cpp \
    detector.cpp \
    mybluetooth.cpp \
    phone.cpp \
    sirene.cpp \
    mysirenethread.cpp

HEADERS  += \
    mywindow.h \
    detector.h \
    mybluetooth.h \
    phone.h \
    sirene.h \
    mysirenethread.h

FORMS    +=
