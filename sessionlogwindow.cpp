#include "sessionlogwindow.h"
#include "ui_sessionlogwindow.h"
#include "batterymanager.h"
#include "session.h"
#include "mainmenu.h"

#include <QStandardItemModel> // Include the necessary header for QStandardItemModel
#include <QMessageBox>
#include <QString>
#include "pcwindow.h"

SessionLogWindow::SessionLogWindow(QWidget *parent, BatteryManager* batM,MainMenu* m) :
    QMainWindow(parent),
    ui(new Ui::SessionLogWindow)
{
    ui->setupUi(this);

    batteryManager = batM;
    batteryBar = findChild<QProgressBar*>("batteryBar");
    mainMenu = m;
    //get sessions

    allSessions = m->getSessions();

    /*delete aft*/
    for (Session* session : allSessions) {
        QString sessionString = session->toString(); // Assuming toString() returns session details
        cout << "Session string: " << endl << sessionString.toStdString() ;
    }


    connect(batteryManager, &BatteryManager::batteryPercentageChanged, this, &SessionLogWindow::updateBatteryBar);

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
    allSessions = mainMenu->getSessions();
    PopulateListView(ui->listView_2, allSessions);
}

void SessionLogWindow::PopulateListView(QListView* view, std::vector<Session*> sessions)
{

    QStandardItemModel *model = new QStandardItemModel();

    // Populate the model with session details
    for (Session* session : sessions) {
        QString sessionString = session->toString(); // Assuming toString() returns session details
        QStandardItem *listItem = new QStandardItem(sessionString);
        model->appendRow(listItem);
    }

    // Set the model for listView_2
    view->setModel(model); //I want the use the view that is passed in
}

void SessionLogWindow::on_pushButton_clicked()
{
    updateSessionLog();

}




void SessionLogWindow::on_addCart_clicked()
{
    int row =  ui->listView_2->selectionModel()->selectedIndexes().first().row();
    std::cout<<"Index:" + std::to_string(row) << std::endl;;
    Session* sesh = allSessions.at(row);

    //TODO make sure this session isnt already in the vector
    sessionsForPC.push_back(sesh);

    PopulateListView(ui->listView,sessionsForPC);
}


void SessionLogWindow::on_sendAll_clicked()
{
    //Open PC
    PCWindow* pcWindow = new PCWindow(this);

    pcWindow->show();

}

