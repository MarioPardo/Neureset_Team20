#include "datetimewindow.h"
#include "ui_datetimewindow.h"

datetimewindow::datetimewindow(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::datetimewindow)
{
    ui->setupUi(this);

    connect(ui->dateTimeEdit, &QDateTimeEdit::dateTimeChanged, [&](const QDateTime &dateTime) {
        qDebug() << "New date and time: " << dateTime.toString();
    });

    //connect(ui->dateTimeEdit, &QDateTimeEdit::dateTimeChanged, this, &datetimewindow::ondateTimeChanged);
}

datetimewindow::~datetimewindow()
{
    delete ui;
}

QDateTimeEdit* datetimewindow::dateTimeEdit() const {
    return editedDateTime;
}

void datetimewindow::ondateTimeChanged(const QDateTime &newDateTime)
{
    emit dateTimeChanged(newDateTime);
}
