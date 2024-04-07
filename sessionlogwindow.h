#ifndef SESSIONLOGWINDOW_H
#define SESSIONLOGWINDOW_H

#include <QMainWindow>
#include <QProgressBar>

class BatteryManager;

namespace Ui {
class SessionLogWindow;
}

class SessionLogWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SessionLogWindow(QWidget *parent = nullptr, BatteryManager* batM = nullptr);
    ~SessionLogWindow();

private slots:

    void updateBatteryBar(int percentage);

private:
    Ui::SessionLogWindow *ui;
    BatteryManager* batteryManager;
    QProgressBar* batteryBar;


};

#endif // SESSIONLOGWINDOW_H
