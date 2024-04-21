#include "datetimewindow.h"
#include "ui_datetimewindow.h"

datetimewindow::datetimewindow(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::datetimewindow)
{
    ui->setupUi(this);

    dateTimeEdit = ui->dateTimeEdit;
    connect(dateTimeEdit, &QDateTimeEdit::dateTimeChanged, this, &datetimewindow::onDateTimeChanged);
}

datetimewindow::~datetimewindow()
{
    delete ui;
}

// slot that emits the signal whenever the date and time are changed in the settings
void datetimewindow::onDateTimeChanged(const QDateTime &dateTime)
{
    emit dateTimeValueChanged(dateTime);
    qDebug() << "Selected Date and Time: " << dateTime.toString("yyyy-MM-dd hh:mm:ss");
}
