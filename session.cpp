#include "session.h"

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
