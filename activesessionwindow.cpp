#include "activesessionwindow.h"
#include "ui_activesessionwindow.h"
#include "device.h"
#include "main.cpp"
#include "mainmenu.h"

#include <QMessageBox>

#include <iostream>

ActiveSessionWindow::ActiveSessionWindow(QWidget *parent, BatteryManager* batM, MainMenu* m):
    QMainWindow(parent),
    ui(new Ui::ActiveSessionWindow)
{
    ui->setupUi(this);

    batteryManager = batM;
    mainMenu = m;

    //setup ui elements
    greenLED = findChild<QFrame*>("greenLED_Frame");
    blueLED = findChild<QFrame*>("blueLED_Frame");
    redLED = findChild<QFrame*>("redLED_Frame");

    displayArea = findChild<QPlainTextEdit*>("display_TextEdit");
    sessionProgressBar = findChild<QProgressBar*>("timeRemainingLabel");
    timeRemainingLabel = findChild<QLabel*>("remainingTime_lbl");
    sensorSpinBox = findChild<QSpinBox*>("sensor_spinBox");
    batteryBar = findChild<QProgressBar*>("batteryBar");

    connect(batteryManager, &BatteryManager::batteryPercentageChanged, this, &ActiveSessionWindow::updateBatteryBar);

    device = new Device(nullptr, batteryManager,mainMenu);
}

ActiveSessionWindow::~ActiveSessionWindow()
{
    delete ui;
}

void ActiveSessionWindow::updateBatteryBar(int percentage)
{
    ui->batteryBar->setValue(percentage);

    if (percentage <= 0) {
        QMessageBox::critical(this, "Device Lost All Power", "DEVICE LOST ALL POWER");

        qApp->quit();
    }

}

void ActiveSessionWindow::on_stop_Btn_clicked()
{
    device->stop();
}


void ActiveSessionWindow::on_play_Btn_clicked()
{
    device->StartSession();
}


void ActiveSessionWindow::on_pause_Btn_clicked()
{
    device->pause();
}


void ActiveSessionWindow::on_powerBtn_clicked()
{
    std::cout << "TURNING OFF DEVICE" <<std::endl;
}


void ActiveSessionWindow::on_menu_Btn_clicked()
{
    std::cout << "GOING BACK TO MAIN MENU" <<std::endl;
}


void ActiveSessionWindow::on_disconnect_Btn_clicked()
{
    device->SensorDisconnected(sensorSpinBox->value());
}

