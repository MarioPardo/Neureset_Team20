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

    // Sensor initialization code (for testing)
    // Sensor* s = new Sensor(1, EEGFrequencyType::DELTA); // For testing
    // QVector<QPair<int, float>> data = s->generateVoltageGraphData(); // For testing

    BatteryManager batteryManager;
    batteryManager.startBatterySimulation();
    w.SetBatteryManager(&batteryManager);

    QVector<Session> sessionInfo;
    QDateTime currentDateTime = QDateTime::currentDateTime();
    sessionInfo.append(Session(currentDateTime, 1, 2, 3));

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
