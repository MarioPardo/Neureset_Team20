#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);
}

MainMenu::~MainMenu()
{
    delete ui;
}


void MainMenu::on_newsession_Btn_clicked()
{
    //open new session UI

}


void MainMenu::on_sessionlog_Btn_clicked()
{
    //open session log UI
}


void MainMenu::on_datentime_Btn_clicked()
{
    //show date and time for device
}


void MainMenu::on_power_Btn_clicked()
{
    //power off device?? either null screen or exit()
}


void MainMenu::on_batteryBar_valueChanged(int value)
{
    //check if slider to 0 for battery, if so start a timer and send popup to "charge battery"
}

