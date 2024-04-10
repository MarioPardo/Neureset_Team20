#ifndef GRAPHDATA_H
#define GRAPHDATA_H

#include <QObject>
#include <QVector>
#include <QPair>
#include "Sensor.h" // Include the header file for the Sensor class

class GraphData : public QObject {
    Q_OBJECT
public:
    explicit GraphData(QObject* parent = nullptr);

    void updateData(int index, const QVector<QPair<int, float>>& newData);

signals:
    void dataUpdated(int index, const QVector<QPair<int, float>>& newData);

private:
    QVector<QPair<int, float>> data[7];
};

#endif // GRAPHDATA_H
