#ifndef PCWINDOW_H
#define PCWINDOW_H

#include <QMainWindow>
#include <vector>

class Session;

namespace Ui {
class PCWindow;
}

class PCWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PCWindow(QWidget *parent = nullptr);
    ~PCWindow();

private slots:
    void on_closeButton_clicked();

private:
    Ui::PCWindow *ui;

    void parseSessions();
    std::vector<Session*> allSessions;

    void populateSessionsView();
};

#endif // PCWINDOW_H
