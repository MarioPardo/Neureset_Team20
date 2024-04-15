#include "session.h"
#include <iostream>
#include <QDateTime>

Session::Session(QDateTime date, float fb, float sb)
{
    dateTime = date;
    firstBaseline = fb;
    secondBaseline = sb;
}

QDateTime Session::getDateTime()
{
    return dateTime;
}

float Session::getFirstBaseline()
{
    return firstBaseline;
}

float Session::getSecondBaseline()
{
    return secondBaseline;
}

QString Session::toString() const {
    return dateTime.toString();
}

void Session::updateDateTime(const QDateTime &newDateTime)
{
    dateTime = newDateTime;
    std::cout << "CURRENT DATETIME: " << dateTime.toString("yyyy-MM-dd hh:mm:ss").toStdString() << std::endl;
    //std::cout << dateTime.toString() << std::endl;
}
