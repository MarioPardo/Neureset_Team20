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
class MainMenu;

class Device;

namespace Ui {
class ActiveSessionWindow;
}

class ActiveSessionWindow : public QMainWindow
{
    Q_OBJECT

public:
    ActiveSessionWindow(QWidget *parent = nullptr, BatteryManager* batM = nullptr,MainMenu* m = nullptr);
    ~ActiveSessionWindow();

    QFrame* greenLED;
    QFrame* blueLED;
    QFrame* redLED;

    MainMenu* mainMenu;

    BatteryManager* batteryManager;
    QProgressBar* batteryBar;

    QPlainTextEdit* displayArea;
    QProgressBar* sessionProgressBar;
    QLabel* timeRemainingLabel;
    QSpinBox* sensorSpinBox;



private slots:

    void updateBatteryBar(int percentage);

    void on_stop_Btn_clicked();

    void on_play_Btn_clicked();

    void on_pause_Btn_clicked();

    void on_powerBtn_clicked();

    void on_menu_Btn_clicked();

    void on_disconnect_Btn_clicked();

    void on_wave_Btn_clicked();

private:
    Ui::ActiveSessionWindow *ui;

    Device* device;
};

#endif // ACTIVESESSIONWINDOW_H
