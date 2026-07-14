#pragma once

#include "MinesweeperBoard.h"

#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include <QMouseEvent>

struct TileCoordinates
{
    int rowNo = 0;
    int colNo = 0;
};

class MinesweeperQtTile : public QPushButton
{
    Q_OBJECT

    TileCoordinates coord;

public:
    explicit MinesweeperQtTile(int r, int c, QWidget *parent = nullptr);
    TileCoordinates getTileCoordinates();

signals:
    void leftclicked();
    void rightclicked();

protected:
    void mousePressEvent(QMouseEvent *) override;
};