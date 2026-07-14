#pragma once

#include "MinesweeperBoard.h"
#include "MinesweeperQtTile.h"

#include <iostream>
#include <vector>

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include <QMouseEvent>

class GameWindow : public QWidget
{
    Q_OBJECT

private:
    std::vector<std::vector<MinesweeperQtTile *>> GameGrid;
    MinesweeperBoard *GameBoard;

    void ReDrawBoard();

private slots:
    // The functions that execute when the click signal fires
    void onLeftClick();
    void onRightClick();

public:
    GameWindow(int HSize, int VSize, QWidget *parent = nullptr);
    ~GameWindow();
};