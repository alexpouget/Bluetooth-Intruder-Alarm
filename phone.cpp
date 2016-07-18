#include "phone.h"

Phone::Phone()
{
    name = "";
    adresse = "";
}

Phone::Phone(std::string _name,std::string _adresse){
    name = _name;
    adresse = _adresse;
}


std::string Phone::getName(){
    return name;
}

std::string Phone::getAdresse(){
    return adresse;
}
