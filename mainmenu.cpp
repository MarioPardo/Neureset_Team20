#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QApplication>
#include <QDialog>
#include <QMainWindow>
#include "batterymanager.h"
#include <QMessageBox>
#include "sessionlogwindow.h"
#include "datetimewindow.h"
#include <QDateTimeEdit>


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
    ActiveSessionWindow::instance(this,batteryManager,this)->show();
}


void MainMenu::on_sessionlog_Btn_clicked()
{
    cout << endl << "Session log opened." <<  endl;
    SessionLogWindow* SLW = new SessionLogWindow(this,batteryManager,this); // Create an instance of SecondWindow

    SLW->show();

}


void MainMenu::on_datentime_Btn_clicked()
{
    datetimewindow* DTW = new datetimewindow();
    connect(DTW, &datetimewindow::dateTimeValueChanged, this, &MainMenu::handleDateTimeValueChanged);

    DTW->show();
}


void MainMenu::on_power_Btn_clicked()
{
    cout << endl << "Power out" << endl;
    QApplication::quit();
}


vector<Session*> MainMenu::getSessions() const {
    return sessions;
}

// updates selectedDateTime variable
void MainMenu::handleDateTimeValueChanged(const QDateTime &dateTime) {
    selectedDateTime = dateTime;
}

QDateTime MainMenu::getSelectedDateTime() const
{
    // returns the selected date and time if the user selects a date and time in the settings
    if (selectedDateTime.isValid()) {
        return selectedDateTime; 
    }
    // else, returns current date
    else
    {
        return QDateTime::currentDateTime(); 
    }
}
