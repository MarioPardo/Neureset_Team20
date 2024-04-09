#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QDialog>
#include <iostream>
#include <QObject>
#include <vector>
#include "activesessionwindow.h"
#include "sessionlogwindow.h"

class BatteryManager;
class Session;

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainMenu; }
QT_END_NAMESPACE

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    MainMenu(QWidget *parent = nullptr);
    ~MainMenu();
    void addSession(Session*);

    void SetBatteryManager(BatteryManager* batM);

private slots:
    void on_newsession_Btn_clicked();

    void on_sessionlog_Btn_clicked();

    void on_datentime_Btn_clicked();

    void on_batteryBar_valueChanged(int value);

    void on_power_Btn_clicked();

    void updateBatteryBar(int percentage);
signals:
    void sessionAddedSignal(Session* session);
private:
    Ui::MainMenu *ui;


    vector<Session*> sessions;
    BatteryManager* batteryManager;
    QProgressBar* batteryBar;


};
#endif // MAINMENU_H
