#ifndef SESSION_H
#define SESSION_H

#include <QDateTime>

class Session
{
public:
    Session(QDateTime date, float fb, float sb, float avg);

    QDateTime getDateTime();
    float getFirstBaseline();
    float getSecondBaseline();
    float getAverageFrequency();

private:
    QDateTime dateTime;
    float firstBaseline;
    float secondBaseline;
    float averageFrequency;

};

#endif // SESSION_H
