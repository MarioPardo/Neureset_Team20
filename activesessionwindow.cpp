#include "activesessionwindow.h"
#include "ui_activesessionwindow.h"
#include "device.h"
#include "main.cpp"
#include "mainmenu.h"

#include <QThread>

#include <QMessageBox>
#include "waveformwindow.h"
#include <iostream>

ActiveSessionWindow* ActiveSessionWindow::m_instance = nullptr;

ActiveSessionWindow::ActiveSessionWindow(QWidget *parent, BatteryManager* batM, MainMenu* m):
    QMainWindow(parent),
    ui(new Ui::ActiveSessionWindow)
{
    ui->setupUi(this);

    batteryManager = batM;
    mainMenu = m;

    //setup ui elements
    greenLED = findChild<QFrame*>("greenLED_Frame");
    blueLED = findChild<QFrame*>("blueLED_Frame");
    redLED = findChild<QFrame*>("redLED_Frame");

    displayArea = findChild<QPlainTextEdit*>("plainTextEdit");
    sessionProgressBar = findChild<QProgressBar*>("timeRemainingLabel");
    timeRemainingLabel = findChild<QLabel*>("remainingTime_lbl");
    sensorSpinBox = findChild<QSpinBox*>("sensor_spinBox");
    batteryBar = findChild<QProgressBar*>("batteryBar");

    connect(batteryManager, &BatteryManager::batteryPercentageChanged, this, &ActiveSessionWindow::updateBatteryBar);

    device = new Device(nullptr, batteryManager,mainMenu, displayArea,this);
    device->setLEDLights(greenLED,blueLED,redLED);

}

ActiveSessionWindow* ActiveSessionWindow::instance(QWidget *parent, BatteryManager* batM, MainMenu* m)
{
    if (!m_instance) {
        m_instance = new ActiveSessionWindow(parent, batM, m);
        std::cout<<"Creating new Active Session Window" << std::endl;
    }
    return m_instance;
}

ActiveSessionWindow::~ActiveSessionWindow()
{
    delete ui;
}

void ActiveSessionWindow::updateBatteryBar(int percentage)
{
    ui->batteryBar->setValue(percentage);

    if (percentage <= 0) {
        QMessageBox::critical(this, "Device Lost All Power", "DEVICE LOST ALL POWER");

        qApp->quit();
    }

}

void ActiveSessionWindow::updateProgress(int secondsRemaining)
{
    if (secondsRemaining < 0)
        secondsRemaining = 0;

    int percent = ((SESSION_LENGTH - secondsRemaining) * 100 / SESSION_LENGTH);

    std::string timeString;
    if (secondsRemaining < 10)
        timeString = "00:0" + std::to_string(secondsRemaining);
    else
        timeString = "00:" + std::to_string(secondsRemaining);



    timeRemainingLabel->setText(QString::fromStdString(timeString));
    ui->sessionProgressBar->setValue(percent);
}


void ActiveSessionWindow::on_stop_Btn_clicked()
{
    device->stop();
    QTimer::singleShot(2000, [this]() //so that display is shown for a little before closing
    {
        m_instance = nullptr;
        delete device;
        this->close();
    });
}


void ActiveSessionWindow::on_play_Btn_clicked()
{
    device->StartSession();
}


void ActiveSessionWindow::on_pause_Btn_clicked()
{
    device->pause();
}


void ActiveSessionWindow::on_power_Btn_clicked()
{
    std::cout << "TURNING OFF DEVICE" <<std::endl;
    on_stop_Btn_clicked();
}


void ActiveSessionWindow::on_menu_Btn_clicked()
{
    this->showMinimized();
}


void ActiveSessionWindow::on_disconnect_Btn_clicked()
{
    device->SensorDisconnected(sensorSpinBox->value());
}

void ActiveSessionWindow::on_wave_Btn_clicked()
{
    cout << endl << "Waveform window opened." <<  endl;
    WaveformWindow* WW = new WaveformWindow(nullptr,batteryManager); // Create an instance of SecondWindow
    //connect waveform window and active session window slots/signals
    connect(WW, &WaveformWindow::selectElectrode, this, &ActiveSessionWindow::handleElectrodeSelected);
    connect(this, &ActiveSessionWindow::updateWave, WW, &WaveformWindow::updateGraph);
    WW->show();
}

void ActiveSessionWindow::handleElectrodeSelected(int index){
    QVector<QPair<int, float>> sensorData = device->getSensor(index)->generateVoltageGraphData();
    emit updateWave(sensorData);
}
