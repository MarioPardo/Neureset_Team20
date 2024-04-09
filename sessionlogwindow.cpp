#include "sessionlogwindow.h"
#include "ui_sessionlogwindow.h"
#include "batterymanager.h"
#include "session.h"

#include <QMessageBox>

SessionLogWindow::SessionLogWindow(QWidget *parent, BatteryManager* batM, std::vector <Session*> vec) :
    QMainWindow(parent),
    ui(new Ui::SessionLogWindow)
{
    ui->setupUi(this);

    batteryManager = batM;
    batteryBar = findChild<QProgressBar*>("batteryBar");


    checkoutSessions = vec;
    connect(batteryManager, &BatteryManager::batteryPercentageChanged, this, &SessionLogWindow::updateBatteryBar);
}

SessionLogWindow::~SessionLogWindow()
{
    delete ui;
}


void SessionLogWindow::updateBatteryBar(int percentage)
{
    ui->batteryBar->setValue(percentage); // Update the progress bar

    if (percentage <= 0) {
        QMessageBox::critical(this, "Device Lost All Power", "DEVICE LOST ALL POWER");

        qApp->quit();
    }
}
