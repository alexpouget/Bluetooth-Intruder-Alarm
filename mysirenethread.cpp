#include "mysirenethread.h"


MySireneThread::MySireneThread() : QThread()
{
}

void MySireneThread::emitStart(){
     emit myStart();
}

void MySireneThread::emitStop(){
    emit MyStop();
}



