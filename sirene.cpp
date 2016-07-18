#include "sirene.h"

Sirene::Sirene()
{

}

void Sirene::alerte(){
    flag = true;
    while(flag){
        system("aplay /home/pi/Documents/project/qtest/sans_titre/615.wav");

    }
}

void Sirene::setFalse(){
    flag = false;
}
