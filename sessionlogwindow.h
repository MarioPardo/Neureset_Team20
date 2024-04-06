#ifndef SESSIONLOGWINDOW_H
#define SESSIONLOGWINDOW_H

#include <QMainWindow>

class BatteryManager;

namespace Ui {
class SessionLogWindow;
}

class SessionLogWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SessionLogWindow(QWidget *parent = nullptr);
    ~SessionLogWindow();

    void setBatteryManager(BatteryManager* batM);
private:
    Ui::SessionLogWindow *ui;
    BatteryManager* batteryManager;

};

#endif // SESSIONLOGWINDOW_H
