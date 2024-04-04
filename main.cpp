#include "mainmenu.h"
#include "sensor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainMenu w;
    w.show();
    Sensor* s = new Sensor(1, EEGFrequencyType::DELTA);
    s->getVoltageGraphData();
    return a.exec();
}
