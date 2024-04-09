#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QApplication>
#include <QDialog>
#include <QMainWindow>
#include "batterymanager.h"
#include <QMessageBox>

using namespace std;

MainMenu::MainMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainMenu)
{
    std::cout << "Main Menu Constructor" << std::endl;

    ui->setupUi(this);

    batteryBar = findChild<QProgressBar*>("batteryBar");
}

MainMenu::~MainMenu()
{
    delete ui;
}


void MainMenu::addSession(Session* session)
{
    sessions.push_back(session); // Store pointer to Device object in log
    std::cout << "Session added" << std::endl;
    //update array in sessionlog?
    emit sessionAddedSignal(session);





}


void MainMenu::SetBatteryManager(BatteryManager* batM)
{
    batteryManager = batM;

    //now connect to slot
    connect(batteryManager, &BatteryManager::batteryPercentageChanged, this, &MainMenu::updateBatteryBar);
}

void MainMenu::updateBatteryBar(int percentage)
{
    ui->batteryBar->setValue(percentage);

    if (percentage <= 0) {
        QMessageBox::critical(this, "Device Lost All Power", "DEVICE LOST ALL POWER");

        qApp->quit();
    }
}

void MainMenu::on_newsession_Btn_clicked()
{
    //open new session UI
    cout <<endl << "New session opened." << endl ;

    ActiveSessionWindow* sessionWindow = new ActiveSessionWindow(this,batteryManager,this); // Create an instance of SecondWindow
    sessionWindow->show();
}


void MainMenu::on_sessionlog_Btn_clicked()
{
    cout << endl << "Session log opened." <<  endl;
    SessionLogWindow* SLW = new SessionLogWindow(this,batteryManager, sessions,this); // Create an instance of SecondWindow
    SLW->show();

}


void MainMenu::on_datentime_Btn_clicked()
{
    cout << endl <<"Current Date and time: "  <<  endl;
}



void MainMenu::on_power_Btn_clicked()
{
    //power off device?? either null screen or exit()
    cout << endl << "Power out" << endl;
}


void MainMenu::on_batteryBar_valueChanged(int value)
{

}

