#include "waveformwindow.h"
#include "ui_waveformwindow.h"

WaveformWindow::WaveformWindow(QWidget *parent, BatteryManager* batM)
    : QWidget(parent)
    , ui(new Ui::WaveformWindow)
{
    ui->setupUi(this);

    ui->customPlot->addGraph();
    this->batteryManager = batM;
    ui->customPlot->xAxis->setRange(0, 60);
    ui->customPlot->yAxis->setRange(0, 20);


}

WaveformWindow::~WaveformWindow()
{
    delete ui;
}
