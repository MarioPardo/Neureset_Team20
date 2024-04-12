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

    // Sensor initialization code (for testing)
    // Sensor* s = new Sensor(1, EEGFrequencyType::DELTA); // For testing
    // QVector<QPair<int, float>> data = s->generateVoltageGraphData(); // For testing

    BatteryManager batteryManager;
    batteryManager.startBatterySimulation();
    w.SetBatteryManager(&batteryManager);

    return a.exec();
}
