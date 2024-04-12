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

    return a.exec();
}
