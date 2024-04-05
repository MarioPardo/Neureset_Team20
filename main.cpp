#include "mainmenu.h"
#include "sensor.h"
#include "batterymanager.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainMenu w;
    w.show();

    // Sensor initialization code (for testing)
    Sensor* s = new Sensor(1, EEGFrequencyType::DELTA); // For testing
    s->getVoltageGraphData(); // For testing


    BatteryManager batteryManager;
    batteryManager.startBatterySimulation();
    w.SetBatteryManager(&batteryManager);

    return a.exec();
}
