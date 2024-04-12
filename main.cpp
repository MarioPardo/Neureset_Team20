#include "mainmenu.h"
#include "batterymanager.h"
#include "session.h"
#include <iostream>
#include <QApplication>
#include <QVector>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainMenu w;
    w.show();

    BatteryManager batteryManager;
    batteryManager.startBatterySimulation();
    w.SetBatteryManager(&batteryManager);

    QVector<Session> sessionInfo;
    QDateTime currentDateTime = QDateTime::currentDateTime();
    sessionInfo.append(Session(currentDateTime, 0, 0, 0));

    for (int i = 0; i < sessionInfo.size(); ++i) {
        Session &session = sessionInfo[i];
        std::cout << "Date and Time: " << session.getDateTime().toString().toStdString()
                  << " First Baseline: " << session.getFirstBaseline()
                  << " Second Baseline: " << session.getSecondBaseline()
                  << " Average Frequency: " << session.getAverageFrequency()
                  << std::endl;
    }
    return a.exec();
}
