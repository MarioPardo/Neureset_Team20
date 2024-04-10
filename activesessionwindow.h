#ifndef ACTIVESESSIONWINDOW_H
#define ACTIVESESSIONWINDOW_H

#include <QMainWindow>
#include <QFrame>
#include <QPlainTextEdit>
#include <QProgressBar>
#include <QLabel>
#include <QApplication>
#include <QSpinBox>

class BatteryManager;

class Device;

namespace Ui {
class ActiveSessionWindow;
}

class ActiveSessionWindow : public QMainWindow
{
    Q_OBJECT

public:
    ActiveSessionWindow(QWidget *parent = nullptr, BatteryManager* batM = nullptr);
    ~ActiveSessionWindow();

    QFrame* greenLED;
    QFrame* blueLED;
    QFrame* redLED;

    BatteryManager* batteryManager;
    QProgressBar* batteryBar;

    QPlainTextEdit* displayArea;
    QProgressBar* sessionProgressBar;
    QLabel* timeRemainingLabel;
    QSpinBox* sensorSpinBox;

signals:
    void openWaveformWindow();
    void updateWave(QVector<QPair<int, float>>& graphData);


private slots:

    void updateBatteryBar(int percentage);

    void on_stop_Btn_clicked();

    void on_play_Btn_clicked();

    void on_pause_Btn_clicked();

    void on_powerBtn_clicked();

    void on_menu_Btn_clicked();

    void on_disconnect_Btn_clicked();

    void on_wave_Btn_clicked();

    void handleElectrodeSelected(int index);

private:
    Ui::ActiveSessionWindow *ui;

    Device* device;
};

#endif // ACTIVESESSIONWINDOW_H
