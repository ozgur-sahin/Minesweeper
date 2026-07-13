#pragma once

#include "MinesweeperBoard.h"

#include <iostream>
#include <vector>

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QString>

class GameWindow : public QWidget
{
    Q_OBJECT

private:
    // QPushButton *myButton; // 1. Store a pointer to the button
    std::vector<std::vector<QPushButton *>> GameGrid;
    MinesweeperBoard *GameBoard;

    void ReDrawBoard();

private slots:
    // 6. The function that executes when the click signal fires
    void onButtonClicked();

public:
    GameWindow(QWidget *parent = nullptr, int HSize = 400, int VSize = 400);
    ~GameWindow();
};