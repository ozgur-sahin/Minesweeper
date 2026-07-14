#pragma once
// #include <random>
#include <vector>
#include <stdexcept>
#include "ConfigStructs.h"
// #include <utility>
#define MINECOUNT 10

struct BoardTile
{
    bool isMine = false;
    bool isRevealed = false;
    bool isFlagged = false;
    int neighborMines = 0;
};

class MinesweeperBoard
{
private:
    BoardSize *Size;
    std::vector<std::vector<BoardTile>> Grid;
    void InitializeMines(int, int, int);
    void setBoardSize(int, int);
    void initializeBoard();
    bool isGameOver = false;
    bool isGameWon = false;
    bool isBoardInitialized = false;
    int CalculateNeighborMines(int, int);
    int TotalMines;
    int RemainingMines;
    int RevealedTiles = 0;

public:
    MinesweeperBoard(MineSweeperConfig *);
    void DrawBoardASCII();
    BoardSize getBoardSize();
    void RevealTile(int, int);
    bool GetGameOverState();
    void DrawBoardFull();
    void ToggleFlagTile(int, int);
    bool GetGameWonState();
    bool GetRevealedState(int, int);
    int GetNeighborMines(int, int);
    bool GetIsMine(int, int);
    bool GetFlaggedState(int, int);
};