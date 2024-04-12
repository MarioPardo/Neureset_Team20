#include "mainmenu.h"
#include "batterymanager.h"
#include "datetimewindow.h"

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

<<<<<<< HEAD
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
=======
>>>>>>> 88132195f6008544538651bbc629e22c7dcf7d87
    return a.exec();
}
