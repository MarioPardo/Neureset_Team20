#include "waveformwindow.h"
#include "batterymanager.h"
#include "ui_waveformwindow.h"

WaveformWindow::WaveformWindow(QWidget *parent, BatteryManager* batM)
    : QWidget(parent)
    , ui(new Ui::WaveformWindow)
{
    ui->setupUi(this);

    ui->customPlot->addGraph();
    this->batteryManager = batM;
    ui->customPlot->xAxis->setRange(0, 60);
    ui->customPlot->yAxis->setRange(0, 30);

    connect(batteryManager, &BatteryManager::batteryPercentageChanged, this, &WaveformWindow::updateBatteryBar);
}

void WaveformWindow::updateGraph(QVector<QPair<int, float>>& graphData) {
    qDebug() << "reaching heeeerrrreee";
    qDebug() << graphData.at(2);
    ui->customPlot->graph(0)->data().data()->clear();
    for(QPair<int, float> dataPoint: graphData) {
        int x = dataPoint.first;
        int y = dataPoint.second;
        ui->customPlot->graph(0)->addData(x, y);
        ui->customPlot->replot();
    }
}

void WaveformWindow::on_electrodeSelectionButton_pressed() {
    int index = ui->electrodeSelector->value() - 1;
    emit selectElectrode(index);
}


void WaveformWindow::updateBatteryBar(int percentage)
{
    ui->batteryBar->setValue(percentage); // Update the progress bar

    if (percentage <= 0) {
        QMessageBox::critical(this, "Device Lost All Power", "DEVICE LOST ALL POWER");

        qApp->quit();
    }
}


WaveformWindow::~WaveformWindow()
{
    delete ui;
}
