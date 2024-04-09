#ifndef WAVEFORMWINDOW_H
#define WAVEFORMWINDOW_H

#include <QWidget>


class BatteryManager;

namespace Ui {
class WaveformWindow;
}

class WaveformWindow : public QWidget
{
    Q_OBJECT

public:
    WaveformWindow(QWidget *parent = nullptr, BatteryManager* batM = nullptr);
    ~WaveformWindow();
    BatteryManager* batteryManager;

private:
    Ui::WaveformWindow *ui;

};

#endif // WAVEFORMWINDOW_H
