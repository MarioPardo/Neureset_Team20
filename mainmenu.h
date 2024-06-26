#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QDialog>
#include <iostream>
#include <QObject>
#include <vector>
#include "activesessionwindow.h"
#include "qdatetime.h"

class BatteryManager;
class Session;
class SessionLogWindow;

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
    vector<Session*> getSessions() const;

    QDateTime getSelectedDateTime() const;


private slots:
    void on_newsession_Btn_clicked();

    void on_sessionlog_Btn_clicked();

    void on_datentime_Btn_clicked();

    void on_power_Btn_clicked();

    void updateBatteryBar(int percentage);

    void handleDateTimeValueChanged(const QDateTime &dateTime);

private:
    Ui::MainMenu *ui;

    vector<Session*> sessions;
    BatteryManager* batteryManager;
    QProgressBar* batteryBar;
    QDateTime selectedDateTime;

};
#endif // MAINMENU_H
