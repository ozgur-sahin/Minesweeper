#include "MinesweeperBoard.h"
#include "GameWindow.h"
#include "ConfigStructs.h"

#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

#define BOARDSIZEX 5
#define BOARDSIZEY 5

#define QTVERSION true
#define TERMINALVERSION false

Config *conf = new Config;

int terminalgame()
{
    MinesweeperBoard board = MinesweeperBoard(&conf->msconf);
    // board.DrawBoardFull();
    // board.DrawBoardASCII();

    while (1)
    {
        int selectedRow, selectedCol;
        std::cout << "Enter row number: ";
        std::cin >> selectedRow;
        std::cout << "Enter column number: ";
        std::cin >> selectedCol;
        if (selectedRow >= board.getBoardSize().row || selectedCol >= board.getBoardSize().col || selectedRow < 0 || selectedCol < 0)
        {
            std::cout << "Invalid Choice\n";
        }
        else
        {
            board.RevealTile(selectedRow, selectedCol);
            board.DrawBoardASCII();
            if (board.GetGameOverState())
            {
                std::cout << "Game over :(\n";
                break;
            }
            else if (board.GetGameWonState())
            {
                std::cout << "Congratulations! You won!\n";
                break;
            }
        }
    }
    return 0;
}

int qtgame(int argc, char *argv[])
{
    // 1. Initialize the main Qt application manager loop
    QApplication app(argc, argv);

    // 2. Instantiate a basic, empty graphical desktop window widget
    GameWindow window(conf);

    // 4. Force the operating system to render the window visually on screen
    window.show();

    // 5. Hand control over to the application engine loop.
    // It keeps the window open until you click the native 'X' close button.
    return app.exec();
}

int main(int argc, char *argv[])
{
    if (!conf)
    {
        std::cout << "Ding ding ding!!!\n";
        return 1;
    }

    if (QTVERSION)
    {
        qtgame(argc, argv);
    }

    if (TERMINALVERSION)
    {
        terminalgame();
    }

    return 0;
}
