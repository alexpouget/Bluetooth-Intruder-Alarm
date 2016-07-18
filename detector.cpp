#include "detector.h"

Detector::Detector(){
    value = 0;
}

void Detector::work(){
    std::cout<<"Gpio start"<<std::endl;

      if (wiringPiSetup () == -1){
         // emit error();
      }

      pinMode (0, OUTPUT) ;  // pin 17 GPIO WHITE
      pinMode (3, INPUT) ;   // pin 22 GPIO ('detector') button
      pinMode (27, OUTPUT) ;  // pin 16 GPIO YELLOW
      pinMode (29, OUTPUT) ;   // pin 21 GPIO RED

      for (;;)
        {
        std::cout<<"read"<<std::endl;
          digitalWrite (0, 0) ;// On
              while(digitalRead(3)==0){

              }
              digitalWrite (0, 1) ;// Off
              value = 1;
              emit detected();
              std::cout<<digitalRead(3)<<std::endl;
              delay (1500) ;

        }
}


