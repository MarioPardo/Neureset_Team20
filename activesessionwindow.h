#ifndef ACTIVESESSIONWINDOW_H
#define ACTIVESESSIONWINDOW_H

#include <QMainWindow>
#include <QFrame>
#include <QPlainTextEdit>
#include <QProgressBar>
#include <QLabel>
#include <QApplication>


class Device;

namespace Ui {
class ActiveSessionWindow;
}

class ActiveSessionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ActiveSessionWindow(QWidget *parent = nullptr);
    ~ActiveSessionWindow();

    QFrame* greenLED;
    QFrame* blueLED;
    QFrame* redLED;

    QPlainTextEdit* displayArea;
    QProgressBar* sessionProgressBar;
    QLabel* timeRemainingLabel;
    QProgressBar* batteryProgressBar;




private slots:
    void on_stop_Btn_clicked();

    void on_play_Btn_clicked();

    void on_pause_Btn_clicked();

    void on_powerBtn_clicked();

    void on_menu_Btn_clicked();

private:
    Ui::ActiveSessionWindow *ui;

    Device* device;
};

#endif // ACTIVESESSIONWINDOW_H
