#include "sessionlogwindow.h"
#include "ui_sessionlogwindow.h"
#include "batterymanager.h"

SessionLogWindow::SessionLogWindow(QWidget *parent, BatteryManager* batM) :
    QMainWindow(parent),
    ui(new Ui::SessionLogWindow)
{
    ui->setupUi(this);

    batteryManager = batM;
    batteryBar = findChild<QProgressBar*>("batteryBar");

    connect(batteryManager, &BatteryManager::batteryPercentageChanged, this, &SessionLogWindow::updateBatteryBar);
}

SessionLogWindow::~SessionLogWindow()
{
    delete ui;
}


void SessionLogWindow::updateBatteryBar(int percentage)
{
    ui->batteryBar->setValue(percentage); // Update the progress bar
}
