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
    QDateTimeEdit* dateTimeEdit() const;
    ~datetimewindow();

signals:
    void dateTimeChanged(const QDateTime &newDateTime);

public slots:
    void ondateTimeChanged(const QDateTime &newdateTime);

private:
    Ui::datetimewindow *ui;
    QDateTimeEdit *editedDateTime;
};

#endif // DATETIMEWINDOW_H
