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

void PCWindow::parseSessions()
{

}



void PCWindow::readAllAndPrintJson()
{
    std::cout << "Reading session log" << std::endl;

    // Open the file for reading
    QString filePath = QCoreApplication::applicationDirPath() + "/session-log.json";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cout << "Failed to open file for reading: " << file.errorString().toStdString() << std::endl;
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

    // Convert the JSON array to a nicely formatted JSON string
    QByteArray formattedJsonData = jsonDoc.toJson(QJsonDocument::Indented);

    // Output the formatted JSON data to std::cout
    QTextStream(stdout) << formattedJsonData << endl;

}
