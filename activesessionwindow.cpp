#include "activesessionwindow.h"
#include "ui_activesessionwindow.h"

ActiveSessionWindow::ActiveSessionWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ActiveSessionWindow)
{
    ui->setupUi(this);
}

ActiveSessionWindow::~ActiveSessionWindow()
{
    delete ui;
}
