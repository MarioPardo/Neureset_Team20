#ifndef SESSIONLOGWINDOW_H
#define SESSIONLOGWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <QObject>
#include <vector>

class MainMenu;
class BatteryManager;
class Session;

namespace Ui {
class SessionLogWindow;
}

class SessionLogWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SessionLogWindow(QWidget *parent = nullptr, BatteryManager* batM = nullptr, std::vector <Session*> v = std::vector<Session*>(), MainMenu* m = nullptr
                              );
    ~SessionLogWindow();
    MainMenu* mainMenu;
    void updateSessionLog(); // Declaration of updateSessionLog function



private slots:

    void updateBatteryBar(int percentage);    
    void on_pushButton_clicked();

private:
    Ui::SessionLogWindow *ui;
    BatteryManager* batteryManager;
    QProgressBar* batteryBar;
    std::vector<Session*> checkoutSessions;


};

#endif // SESSIONLOGWINDOW_H
