#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainMenu; }
QT_END_NAMESPACE

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private slots:
    void on_newsession_Btn_clicked();

    void on_sessionlog_Btn_clicked();

    void on_datentime_Btn_clicked();

    void on_power_Btn_clicked();

    void on_batteryBar_valueChanged(int value);

private:
    Ui::MainMenu *ui;
};
#endif // MAINMENU_H
