#pragma once

struct BoardSize
{
    int row = 8;
    int col = 8;
};

struct MineSweeperConfig
{
    int minecount = 15;
    BoardSize GameBoardSize;
};

struct QtBoardConfig
{
    int tileSize[2] = {80, 80};
    int windowSize[2] = {400, 400};
};

struct Config
{
    QtBoardConfig qtconf;
    MineSweeperConfig msconf;
};