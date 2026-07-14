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
    // QPushButton *myButton; // 1. Store a pointer to the button
    std::vector<std::vector<MinesweeperQtTile *>> GameGrid;
    MinesweeperBoard *GameBoard;

    void ReDrawBoard();

private slots:
    // 6. The function that executes when the click signal fires
    void onLeftClick();
    void onRightClick();

public:
    GameWindow(QWidget *parent = nullptr, int HSize = 400, int VSize = 400);
    ~GameWindow();
};