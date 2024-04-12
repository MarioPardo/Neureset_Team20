#include "session.h"
#include <iostream>
#include <QDateTime>

Session::Session(QDateTime date, float fb, float sb, float avg)
{
    dateTime = date;
    firstBaseline = fb;
    secondBaseline = sb;
    averageFrequency = avg;
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

float Session::getAverageFrequency()
{
    return averageFrequency;
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
