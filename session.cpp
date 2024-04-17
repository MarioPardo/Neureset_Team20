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

QString Session::toString() const
{
    QString dateString = dateTime.toString("ddd MMM d, yyyy h:mm AP");
    QString firstBaselineString = QString::number(firstBaseline, 'f', 3);
    QString secondBaselineString = QString::number(secondBaseline, 'f', 3);

    return QString("Session On: %1\n    First Baseline: %2 Hz\n    Second Baseline: %3 Hz")
        .arg(dateString)
        .arg(firstBaselineString)
        .arg(secondBaselineString);
}



void Session::updateDateTime(const QDateTime &newDateTime)
{
    dateTime = newDateTime;
    std::cout << "CURRENT DATETIME: " << dateTime.toString("yyyy-MM-dd hh:mm:ss").toStdString() << std::endl;
    //std::cout << dateTime.toString() << std::endl;
}

bool Session::operator==(const Session &other) const {
    if(this->dateTime == other.dateTime) {
        return true;
    }
    return false;
}
