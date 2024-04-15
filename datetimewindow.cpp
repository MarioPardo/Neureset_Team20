#include "datetimewindow.h"
#include "ui_datetimewindow.h"


datetimewindow::datetimewindow(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::datetimewindow)
{
    ui->setupUi(this);

    dateTimeEdit = ui->dateTimeEdit;
    //QDateTime DT = ui->dateTimeEdit->dateTime();
    // connect(ui->dateTimeEdit, &QDateTimeEdit::dateTimeChanged, [&](const QDateTime &dateTime) {
    //    qDebug() << "Date and time changed to: " << dateTime.toString();
    //});
    //connect(ui->dateTimeEdit, &QDateTimeEdit::dateTimeChanged, this, &datetimewindow::ondateTimeChanged);
    connect(dateTimeEdit, &QDateTimeEdit::dateTimeChanged, this, &datetimewindow::onDateTimeChanged);
}

datetimewindow::~datetimewindow()
{
    delete ui;
}


QDateTime datetimewindow::getDateTimeValue() const {
    //return dateTimeValue;
    return dateTimeEdit->dateTime();
}


void datetimewindow::onDateTimeChanged(const QDateTime &dateTime){
    //dateTimeValue = dateTime;
    emit dateTimeValueChanged(dateTime);
    qDebug() << "Selected Date and Time: " << dateTime.toString("yyyy-MM-dd hh:mm:ss");
}
