#ifndef SESSIONLOGWINDOW_H
#define SESSIONLOGWINDOW_H

#include <QMainWindow>

namespace Ui {
class SessionLogWindow;
}

class SessionLogWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SessionLogWindow(QWidget *parent = nullptr);
    ~SessionLogWindow();

private:
    Ui::SessionLogWindow *ui;
};

#endif // SESSIONLOGWINDOW_H
