#include <iostream>
#include <utility>
#include <vector>
#include <random>

#include "MinesweeperBoard.h"

MinesweeperBoard::MinesweeperBoard(MineSweeperConfig *msconf)
{
    int minecount = msconf->minecount;
    Size = &msconf->GameBoardSize;
    setBoardSize(Size->row, Size->col);
    initializeBoard();
    TotalMines = minecount;
    RemainingMines = minecount;
}

void MinesweeperBoard::DrawBoardASCII()
{

    char UnrevealedTileChar = '*';
    char FlaggedTileChar = '#';
    char MineChar = 'o';
    char ZeroMineTileChar = 'x';

    for (std::vector<BoardTile> row : Grid)
    {
        for (BoardTile tile : row)
        {
            if (tile.isFlagged)
            {
                std::cout << FlaggedTileChar;
            }
            else if (!tile.isRevealed)
            {
                std::cout << UnrevealedTileChar;
            }
            else if (tile.isMine)
            {
                std::cout << MineChar;
            }
            else
            {
                if (tile.neighborMines != 0)
                {
                    std::cout << tile.neighborMines;
                }
                else
                {
                    std::cout << ZeroMineTileChar;
                }
            }
        }
        std::cout << '\n';
    }
}

void MinesweeperBoard::initializeBoard()
{
    Grid.resize(Size->row, std::vector<BoardTile>(Size->col));
    // InitializeMines(MINECOUNT);
}

bool MinesweeperBoard::GetGameOverState()
{
    return isGameOver;
}

bool MinesweeperBoard::GetGameWonState()
{
    return isGameWon;
}

void MinesweeperBoard::DrawBoardFull()
{
    char MineChar = 'o';
    for (std::vector<BoardTile> row : Grid)
    {
        for (BoardTile tile : row)
        {
            if (tile.isMine)
            {
                std::cout << MineChar;
            }
            else
            {
                std::cout << '.';
            }
        }
        std::cout << '\n';
    }
}

void MinesweeperBoard::InitializeMines(int minecount, int row, int col)
{

    if (Size->row * Size->col <= minecount - 1)
    {
        throw std::runtime_error(
            "Invalid board configuration.\n\
             More mines to be placed than there are tiles.");
    }
    std::random_device rnd;
    std::mt19937 gen(rnd());

    std::uniform_int_distribution<> disRow(0, Size->row - 1);
    std::uniform_int_distribution<> disCol(0, Size->col - 1);

    int placedMines = 0;

    while (placedMines < minecount)
    {
        int RowNumber = disRow(gen);
        int ColNumber = disCol(gen);
        if (std::abs(RowNumber - row) <= 1 && std::abs(ColNumber - col) <= 1)
        {
            // std::cout << "Mine placement failed at ";
            // std::cout << RowNumber << " " << ColNumber << "\n";
            continue;
        }
        if (!Grid[RowNumber][ColNumber].isMine)
        {
            Grid[RowNumber][ColNumber].isMine = true;
            placedMines++;
            // std::cout << "Mine is placed at ";
            // std::cout << RowNumber << " " << ColNumber << "\n";
        }
    }
    DrawBoardFull();
}

BoardSize MinesweeperBoard::getBoardSize()
{
    return *Size;
}

void inline MinesweeperBoard::setBoardSize(int x, int y)
{
    *Size = {x, y};
}

void MinesweeperBoard::RevealTile(int x, int y)
{
    if (Grid[x][y].isRevealed || Grid[x][y].isFlagged)
    {
        return;
    }
    Grid[x][y].isRevealed = true;

    if (!isBoardInitialized)
    {
        isBoardInitialized = true;
        InitializeMines(TotalMines, x, y);
    }

    if (Grid[x][y].isMine)
    {
        isGameOver = true;
        return;
    }

    RevealedTiles++;
    Grid[x][y].neighborMines = CalculateNeighborMines(x, y);

    if (Grid[x][y].neighborMines == 0)
    {
        for (int h = std::max(x - 1, 0); h <= std::min(x + 1, Size->row - 1); h++)
        {
            for (int v = std::max(y - 1, 0); v <= std::min(y + 1, Size->col - 1); v++)
            {
                if (!Grid[h][v].isRevealed)
                {
                    RevealTile(h, v);
                }
            }
        }
    }

    if (RevealedTiles >= Size->row * Size->col - TotalMines)
    {
        isGameWon = true;
    }
}

int MinesweeperBoard::CalculateNeighborMines(int x, int y)
{
    int MineCount = 0;
    for (int h = std::max(x - 1, 0); h <= std::min(x + 1, Size->row - 1); h++)
    {
        for (int v = std::max(y - 1, 0); v <= std::min(y + 1, Size->col - 1); v++)
        {
            if (Grid[h][v].isMine)
            {
                MineCount++;
            }
        }
    }
    return MineCount;
}

void MinesweeperBoard::ToggleFlagTile(int x, int y)
{
    if (Grid[x][y].isRevealed)
        return;

    Grid[x][y].isFlagged = !Grid[x][y].isFlagged;
    if (Grid[x][y].isFlagged)
    {
        RemainingMines--;
    }
    else
    {
        RemainingMines++;
    }
}

bool MinesweeperBoard::GetRevealedState(int row, int col)
{
    return Grid[row][col].isRevealed;
}

int MinesweeperBoard::GetNeighborMines(int row, int col)
{
    return Grid[row][col].neighborMines;
}

bool MinesweeperBoard::GetIsMine(int row, int col)
{
    return Grid[row][col].isMine;
}

bool MinesweeperBoard::GetFlaggedState(int row, int col)
{
    return Grid[row][col].isFlagged;
}