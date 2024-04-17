#include "pcwindow.h"
#include "ui_pcwindow.h"
#include <QFile>
#include <QJsonDocument>
#include <QDebug>
#include <QTextStream>
#include <iostream>
#include <QJsonArray>
#include <QJsonObject>
#include "session.h"
#include <QStandardItemModel>

PCWindow::PCWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PCWindow)
{
    ui->setupUi(this);

    parseSessions();

    populateSessionsView();


}

PCWindow::~PCWindow()
{
    delete ui;
}

void PCWindow::parseSessions()
{
    std::cout << "Parsing session log" << std::endl;

    // Open the file for reading
    QString filePath = QCoreApplication::applicationDirPath() + "/session-log.json";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file for reading: " << file.errorString() << Qt::endl;
        return;
    }

    // Read the JSON data from the file
    QByteArray jsonData = file.readAll();
    file.close();

    // Parse the JSON data into a QJsonDocument
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
    if (parseError.error != QJsonParseError::NoError)
    {
        std::cout << "Failed to parse JSON data: " << parseError.errorString().toStdString() << std::endl;
        return;
    }

    // Check if the JSON document is an array
    if (!jsonDoc.isArray())
    {
        std::cout << "JSON document is not an array" << std::endl;
        return;
    }

    // Iterate over each session object in the array
    QJsonArray jsonArray = jsonDoc.array();
    for (const QJsonValue& sessionValue : jsonArray)
    {
        // Extract session data from JSON object
        QJsonObject sessionObject = sessionValue.toObject();
        QDateTime dateTime = QDateTime::fromString(sessionObject["DateTime"].toString(), Qt::ISODate);
        float firstBaseline = sessionObject["firstBaseline"].toDouble();
        float secondBaseline = sessionObject["secondBaseline"].toDouble();

        // Create a new Session object and add it to allSessions list
        Session* session = new Session(dateTime, firstBaseline, secondBaseline);

        std::cout<<session->toString().toStdString() <<std::endl;
        allSessions.push_back(session);
    }

    std::cout << "Sessions parsed successfully." << std::endl;
}

void PCWindow::populateSessionsView()
{
    QStandardItemModel *model = new QStandardItemModel();

    // Populate the model with session details
    for (Session* session : allSessions) {
        QString sessionString = session->toString();
        QStandardItem *listItem = new QStandardItem(" ------ \n " + sessionString );
        model->appendRow(listItem);
    }

    ui->listView->setModel(model);

}

void PCWindow::on_closeButton_clicked()
{
    this->close();
    std::cout << std::endl << "Close window";
}

