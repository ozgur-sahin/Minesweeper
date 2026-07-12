#pragma once

#include <iostream>

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class GameWindow : public QWidget
{
    Q_OBJECT

private:
    QPushButton *myButton; // 1. Store a pointer to the button

private slots:
    // 6. The function that executes when the click signal fires
    void onButtonClicked();

public:
    GameWindow(QWidget *parent = nullptr);
};