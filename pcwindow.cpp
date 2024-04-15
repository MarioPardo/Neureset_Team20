#include "pcwindow.h"
#include "ui_pcwindow.h"
#include <QFile>
#include <QJsonDocument>
#include <QDebug>
#include <QTextStream>
#include <iostream>

PCWindow::PCWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PCWindow)
{
    ui->setupUi(this);

    readAllAndPrintJson();
}

PCWindow::~PCWindow()
{
    delete ui;
}

void PCWindow::readSessions()
{

}


void PCWindow::readAllAndPrintJson( )
{
    QString filePath = QCoreApplication::applicationDirPath() + "/session-log.json";
    std::cout<<"Reading from : "<<  filePath.toStdString() << std::endl;

    // Open the JSON file for reading
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Failed to open file for reading: " << file.errorString().toStdString() << std::endl;
        return;
    }

    // Read the JSON data from the file

    QByteArray jsonData = file.readAll();
    jsonData = jsonData.trimmed();
    qDebug() << "JSON Data:" << jsonData;

    // Close the file
    file.close();

    // Parse the JSON data into a QJsonDocument
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        std::cerr << "Failed to parse JSON data: " << parseError.errorString().toStdString() << std::endl;
    }

    // Convert the QJsonDocument to a nicely formatted JSON string
    QByteArray formattedJsonData = jsonDoc.toJson(QJsonDocument::Indented);

    // Output the formatted JSON data to std::cout
    QTextStream(stdout) << formattedJsonData << endl;
}
