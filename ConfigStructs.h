#pragma once

struct BoardSize
{
    int row = 15;
    int col = 15;
};

struct MineSweeperConfig
{
    int minecount = 50;
    BoardSize GameBoardSize;
};

struct QtBoardConfig
{
    int windowSize[2] = {400, 400};
    int tileSize[2] = {80, 80};
};

struct Config
{
    QtBoardConfig qtconf;
    MineSweeperConfig msconf;
};