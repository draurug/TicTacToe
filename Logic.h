#pragma once

#include <QObject>
#include <QVector>

class Logic : public QObject
{
    Q_OBJECT

    static const int GRID_SIZE = 3;
    int m_grid[GRID_SIZE][GRID_SIZE] = {0};

public:
    Logic();

public slots:
    void onClick(int x, int y, int value);

signals:
    void positionChanged(QVector<int>); // Объявляем сигнал с массивом
};
