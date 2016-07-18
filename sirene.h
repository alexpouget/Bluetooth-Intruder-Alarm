#ifndef SIRENE_H
#define SIRENE_H
#include <stdlib.h>
#include <QObject>

class Sirene : public QObject
{
    Q_OBJECT

public:
    Sirene();

signals:

public slots:
    void alerte();
    void setFalse();
private:
    bool flag;
};

#endif // SIRENE_H
