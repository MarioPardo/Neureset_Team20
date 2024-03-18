#ifndef ACTIVESESSIONWINDOW_H
#define ACTIVESESSIONWINDOW_H

#include <QMainWindow>

namespace Ui {
class ActiveSessionWindow;
}

class ActiveSessionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ActiveSessionWindow(QWidget *parent = nullptr);
    ~ActiveSessionWindow();

private:
    Ui::ActiveSessionWindow *ui;
};

#endif // ACTIVESESSIONWINDOW_H
