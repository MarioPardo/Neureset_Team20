#include "sessionlogwindow.h"
#include "ui_sessionlogwindow.h"

SessionLogWindow::SessionLogWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SessionLogWindow)
{
    ui->setupUi(this);
}

SessionLogWindow::~SessionLogWindow()
{
    delete ui;
}
