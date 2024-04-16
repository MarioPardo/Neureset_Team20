#include "sessionlogwindow.h"
#include "ui_sessionlogwindow.h"
#include "batterymanager.h"
#include "session.h"
#include "mainmenu.h"

#include <QStandardItemModel> // Include the necessary header for QStandardItemModel
#include <QMessageBox>
#include <QString>
#include "pcwindow.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

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
        QString sessionString = session->getDateTime().toString(); // Assuming toString() returns session details
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


void SessionLogWindow::saveSession(Session* session)
{
    std::cout << "Saving session" << std::endl;

    // Create a JSON object for the session
    QJsonObject sessionObject;

    // Convert QDateTime to QString
    QString dateTimeString = session->getDateTime().toString(Qt::ISODate);

    // Assign session data to the JSON object
    sessionObject["DateTime"] = dateTimeString;
    sessionObject["firstBaseline"] = session->getFirstBaseline();
    sessionObject["secondBaseline"] = session->getSecondBaseline();

    // Create a JSON array if it doesn't exist in the file
    QJsonArray jsonArray;

    // Open the file for reading and writing
    QString filePath = QCoreApplication::applicationDirPath() + "/session-log.json";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        std::cout << "Failed opening file: " << file.errorString().toStdString() << std::endl;
        return;
    }

    // Read existing data from the file, if any
    QByteArray fileData = file.readAll();
    if (!fileData.isEmpty())
    {
        // Parse existing JSON array from file data
        QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
        if (jsonDoc.isArray())
        {
            // Append existing sessions to the array
            jsonArray = jsonDoc.array();
        }
        else
        {
            std::cout << "File does not contain a valid JSON array. Appending sessions as new array." << std::endl;
        }
    }

    // Append the new session object to the array
    jsonArray.append(sessionObject);

    // Write the updated JSON array to the file
    file.seek(0); // Move file pointer to beginning
    file.write(QJsonDocument(jsonArray).toJson());
    file.resize(file.pos()); // Truncate any remaining data

    // Close the file
    file.close();

    std::cout << "Session saved successfully." << std::endl;
}


void SessionLogWindow::on_sendAll_clicked()
{
    for(Session* sesh : sessionsForPC)
    {
        saveSession(sesh);
    }

    //Open PC
    PCWindow* pcWindow = new PCWindow(this);

    pcWindow->show();

}

