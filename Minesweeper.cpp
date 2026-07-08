#include <iostream>
#include <utility>
#include <vector>
#include <random>

#include "Minesweeper.h"

MinesweeperBoard::MinesweeperBoard(int x, int y){
    setBoardSize(x, y);
    initializeBoard();
    TotalMines = MINECOUNT;
    RemainingMines = MINECOUNT;
}

void MinesweeperBoard::DrawBoardASCII(){

    char UnrevealedTileChar = '*';
    char FlaggedTileChar= '#';
    char MineChar='o';
    char ZeroMineTileChar='x';

    for (std::vector<BoardTile> row : Grid){
        for(BoardTile tile:row){
            if(tile.isFlagged){
                std::cout << FlaggedTileChar;
            }
            else if(!tile.isRevealed){
                std::cout << UnrevealedTileChar;
            }
            else if(tile.isMine){
                std::cout << MineChar;
            }
            else{
                if (tile.neighborMines !=0){
                    std::cout << tile.neighborMines;
                }
                else{
                    std::cout << ZeroMineTileChar;
                }
            }
        }
        std::cout << '\n';
    }
}

void MinesweeperBoard::initializeBoard(){
    Grid.resize(Size.row, std::vector<BoardTile>(Size.col));
    InitializeMines(MINECOUNT);
}

bool MinesweeperBoard::GetGameOverState(){
    return isGameOver;
}

bool MinesweeperBoard::GetGameWonState(){
    return isGameWon;
}

void MinesweeperBoard::DrawBoardFull(){
    char MineChar='o';
    for (std::vector<BoardTile> row : Grid){
        for(BoardTile tile : row){
            if(tile.isMine){
                std::cout << MineChar;
            }
            else{
                std::cout << '.';
            }
        }
        std::cout << '\n';
    }
}

void MinesweeperBoard::InitializeMines(int minecount){

    if(Size.row * Size.col <= minecount){
        throw std::runtime_error(
            "Invalid board configuration.\n\
             More mines to be placed than there are tiles.");
    }
    std::random_device rnd;
    std::mt19937 gen(rnd());

    std::uniform_int_distribution<> disRow(0, Size.row - 1);
    std::uniform_int_distribution<> disCol(0, Size.col - 1);

    int placedMines=0;

    while(placedMines < minecount){
        int RowNumber = disRow(gen);
        int ColNumber = disCol(gen);
        if(!Grid[RowNumber][ColNumber].isMine){
            Grid[RowNumber][ColNumber].isMine = true;
            placedMines++;
        }
    }

}

BoardSize MinesweeperBoard::getBoardSize(){
    return Size;
}

void MinesweeperBoard::setBoardSize(int x, int y){
    Size = {x, y};
}

void MinesweeperBoard::RevealTile(int x, int y){
    if(Grid[x][y].isRevealed){
        return;
    }
    Grid[x][y].isRevealed = true;
    if(Grid[x][y].isMine){
        isGameOver = true;
        return;
    }
    RevealedTiles++;
    Grid[x][y].neighborMines = CalculateNeighborMines(x, y);

    if(Grid[x][y].neighborMines == 0){
        for(int h = std::max(x-1, 0); h <= std::min(x+1, Size.row-1); h++){
            for(int v = std::max(y-1, 0); v <= std::min(y+1, Size.col-1); v++){
                if(!Grid[h][v].isRevealed){
                    RevealTile(h,v);
                }
            }
        }
    }

    if(RevealedTiles >= Size.row * Size.col - TotalMines){
        isGameWon = true;
    }
}

int MinesweeperBoard::CalculateNeighborMines(int x, int y){
    int MineCount=0;
    for(int h=std::max(x-1, 0); h<=std::min(x+1, Size.row-1); h++){
        for(int v=std::max(y-1, 0); v<=std::min(y+1, Size.col-1); v++){
            if(Grid[h][v].isMine){
                MineCount++;
            }
        }
    }
    return MineCount;
}

void MinesweeperBoard::ToggleFlagTile(int x, int y){
    Grid[x][y].isFlagged = !Grid[x][y].isFlagged;
    if(Grid[x][y].isFlagged){
        RemainingMines--;
    }
    else{
        RemainingMines++;
    }
}