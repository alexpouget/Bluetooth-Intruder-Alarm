#ifndef PHONE_H
#define PHONE_H
#include <iostream>
#include <QObject>

class Phone: public QObject
{
    Q_OBJECT

public:
    Phone();
    Phone(std::string _name,std::string _adresse);
    std::string getName();
    std::string getAdresse();
signals:

public slots:

private:
    std::string name;
    std::string adresse;
};

#endif // PHONE_H
