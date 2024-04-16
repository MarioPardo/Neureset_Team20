#ifndef SESSION_H
#define SESSION_H

#include <QDateTime>
#include <QString>
#include <QObject>

class Session
{

public:
    Session(QDateTime date, float fb, float sb);

    QDateTime getDateTime();
    float getFirstBaseline();
    float getSecondBaseline();
    QString toString() const; // New toString function declaration



public slots:
    void updateDateTime(const QDateTime &newDateTime);

private:
    QDateTime dateTime;
    float firstBaseline;
    float secondBaseline;

};

#endif // SESSION_H
