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
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "session.h"
#include <QString>

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


void MainMenu::saveSession(Session* session)
{
    std::cout << "Saving session" << std::endl;

    QJsonObject sessionObject;
    sessionObject["DateTime"] = session->getDateTime().toString(Qt::ISODate);
    sessionObject["firstBaseline"] = session->getFirstBaseline();
    sessionObject["secondBaseline"] = session->getSecondBaseline();
    sessionObject["Average"] = session->getAverageFrequency();

    QJsonDocument jsonDoc(sessionObject);

    QString filePath = QCoreApplication::applicationDirPath() + "/session-log.json";
    std::cout << "Saving to : " << filePath.toStdString() << std::endl;

    // Check if the file exists, create it if it doesn't
    QFile file(filePath);
    if (!file.exists()) {
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            std::cout << "Failed to create file" << std::endl;
            return;
        }
        file.close(); // Close the file after creating it
    }

    // Open the file for appending
    if (!file.open(QIODevice::Append | QIODevice::Text))
    {
        std::cout << "Failed opening file" << std::endl;
        return;
    }

    if (file.size() != 0) {
        file.write(","); // Add a comma to separate JSON objects
    }

    qint64 numBytes = file.write(jsonDoc.toJson());
    if (numBytes == -1)
    {
        std::cout << "Failed writing to file" << std::endl;
    }

    file.close();
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
    cout << endl <<"Current Date and time: "  <<  endl;
    datetimewindow* DTW = new datetimewindow();
    DTW->show();

    //session = new Session(this);
   // connect(DTW, &datetimewindow::dateTimeChanged, sessions, &Session::updateDateTime);
   // cout << "Date and Time: " << sessions.getDateTime().toString().toStdString();
}



void MainMenu::on_power_Btn_clicked()
{
    cout << endl << "Power out" << endl;
    QApplication::quit();
}


vector<Session*> MainMenu::getSessions() const {
    return sessions;
}

