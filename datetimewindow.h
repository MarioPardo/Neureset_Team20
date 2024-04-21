#ifndef DATETIMEWINDOW_H
#define DATETIMEWINDOW_H

#include <QFrame>
#include <QDateTime>
#include <QDateTimeEdit>
#include <QDebug>


namespace Ui {
class datetimewindow;
}

class datetimewindow : public QFrame
{
    Q_OBJECT

public:
    explicit datetimewindow(QWidget *parent = nullptr);
    ~datetimewindow();

signals:
    void dateTimeValueChanged(const QDateTime &DateTime);

public slots:
    void onDateTimeChanged(const QDateTime &dateTime);

private:
    Ui::datetimewindow *ui;
    QDateTimeEdit* dateTimeEdit;
};

#endif // DATETIMEWINDOW_H
