#ifndef SESSIONLOGWINDOW_H
#define SESSIONLOGWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <QObject>
#include <vector>
#include <QListView>

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
    explicit SessionLogWindow(QWidget *parent = nullptr, BatteryManager* batM = nullptr, MainMenu* m = nullptr
                              );
    ~SessionLogWindow();
    MainMenu* mainMenu;
    void updateSessionLog(); // Declaration of updateSessionLog function



private slots:

    void updateBatteryBar(int percentage);    
    void on_pushButton_clicked();

    void on_addCart_clicked();

private:
    Ui::SessionLogWindow *ui;
    BatteryManager* batteryManager;
    QProgressBar* batteryBar;
    QListView* allSessionsView;

    std::vector<Session*> allSessions;
    std::vector<Session*> sessionsForPC;

    void PopulateListView(QListView* view, std::vector<Session*> sessions);


};

#endif // SESSIONLOGWINDOW_H
