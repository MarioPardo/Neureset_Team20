#ifndef SESSION_H
#define SESSION_H

#include <QDateTime>
#include <QString>


class Session
{
public:
    Session(QDateTime date, float fb, float sb, float avg);

    QDateTime getDateTime();
    float getFirstBaseline();
    float getSecondBaseline();
    float getAverageFrequency();
    QString toString() const; // New toString function declaration

public slots:
    void updateDateTime(const QDateTime &newDateTime);

private:
    QDateTime dateTime;
    float firstBaseline;
    float secondBaseline;
    float averageFrequency;

};

#endif // SESSION_H
