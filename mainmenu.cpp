#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QApplication>
#include <QDialog>
#include <QMainWindow>
using namespace std;

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
    cout <<endl << "New session opened." << endl ;

    ActiveSessionWindow sessionWindow; // Create an instance of SecondWindow
    sessionWindow.setModal(true);
    sessionWindow.exec();
    //sessionWindow.show();

}


void MainMenu::on_sessionlog_Btn_clicked()
{
    cout << endl << "Session log opened." <<  endl;
    SessionLogWindow SLW; // Create an instance of SecondWindow
    //SLW.show(); // Show the SecondWindow

    //open session log UI
}


void MainMenu::on_datentime_Btn_clicked()
{
    //show date and time for device
    cout << endl <<"Current Date and time: "  <<  endl;
}



void MainMenu::on_power_Btn_clicked()
{
    //power off device?? either null screen or exit()
    cout << endl << "Power out" << endl;
}


void MainMenu::on_batteryBar_valueChanged(int value)
{
    //check if slider to 0 for battery, if so start a timer and send popup to "charge battery"
    cout << "Battery slider changed !";
    if(value < 1)
    {
        cout << "Battery low!";
    }
}

