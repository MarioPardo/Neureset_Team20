#include "sessionlogwindow.h"
#include "ui_sessionlogwindow.h"
#include "batterymanager.h"
#include "session.h"
#include "mainmenu.h"

#include <QStandardItemModel> // Include the necessary header for QStandardItemModel
#include <QMessageBox>
#include <QString>

SessionLogWindow::SessionLogWindow(QWidget *parent, BatteryManager* batM,MainMenu* m) :
    QMainWindow(parent),
    ui(new Ui::SessionLogWindow)
{
    ui->setupUi(this);

    batteryManager = batM;
    batteryBar = findChild<QProgressBar*>("batteryBar");
    mainMenu = m;
    //get sessions


    checkoutSessions = m->getSessions();

    /*delete aft*/
    for (Session* session : checkoutSessions) {
        QString sessionString = session->toString(); // Assuming toString() returns session details
        cout << "Session string: " << endl << sessionString.toStdString() ;
    }


    connect(batteryManager, &BatteryManager::batteryPercentageChanged, this, &SessionLogWindow::updateBatteryBar);

    //connect(mainMenu, &MainMenu::sessionAddedSignal, this, &SessionLogWindow::onSessionAdded);
    updateSessionLog();

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



void SessionLogWindow::updateSessionLog()
{

    checkoutSessions = mainMenu->getSessions();


    QStandardItemModel *model = new QStandardItemModel();

    // Populate the model with session details
    for (Session* session : checkoutSessions) {
        QString sessionString = session->toString(); // Assuming toString() returns session details
        cout << "Session string: " << endl << sessionString.toStdString() ;
        QStandardItem *listItem = new QStandardItem(sessionString);
        model->appendRow(listItem);
    }

    // Set the model for listView_2
    ui->listView_2->setModel(model);
}

void SessionLogWindow::on_pushButton_clicked()
{
    updateSessionLog();

}

