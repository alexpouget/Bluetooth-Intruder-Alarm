#ifndef MYSIRENETHREAD_H
#define MYSIRENETHREAD_H
#include <QThread>

class MySireneThread : public QThread
{

public:
    MySireneThread();
    void emitStart();
    void emitStop();

signals:
    void myStart();
    void MyStop();
public slots:

private:

};
#endif // MYSIRENETHREAD_H
