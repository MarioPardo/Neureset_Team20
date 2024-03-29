#include "activesessionwindow.h"
#include "ui_activesessionwindow.h"
#include "device.h"

#include <iostream>

ActiveSessionWindow::ActiveSessionWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ActiveSessionWindow)
{
    ui->setupUi(this);

    //setup ui elements
    greenLED = findChild<QFrame*>("greenLED_Frame");
    blueLED = findChild<QFrame*>("blueLED_Frame");
    redLED = findChild<QFrame*>("redLED_Frame");

    displayArea = findChild<QPlainTextEdit*>("display_TextEdit");
    sessionProgressBar = findChild<QProgressBar*>("timeRemainingLabel");
    timeRemainingLabel = findChild<QLabel*>("remainingTime_lbl");
    sessionProgressBar = findChild<QProgressBar*>("batteryProgressBar");

    device = new Device();

}

ActiveSessionWindow::~ActiveSessionWindow()
{
    delete ui;
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

