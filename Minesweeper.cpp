#include <iostream>
#include <utility>
#include <vector>
#include <random>

#include "Minesweeper.h"

MinesweeperBoard::MinesweeperBoard(int x, int y){
    this -> setBoardSize(x, y);
    this -> initializeBoard();
    this -> TotalMines = MINECOUNT;
    this -> RemainingMines = MINECOUNT;
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
    Grid.resize(BoardSize.first, std::vector<BoardTile>(BoardSize.second));
    this -> InitializeMines(MINECOUNT);
}

bool MinesweeperBoard::GetGameOverState(){
    return this -> isGameOver;
}

bool MinesweeperBoard::GetGameWonState(){
    return this -> isGameWon;
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
    std::random_device rnd;
    std::mt19937 gen(rnd());

    std::uniform_int_distribution<> disRow(0, this -> BoardSize.first - 1);
    std::uniform_int_distribution<> disCol(0, this -> BoardSize.second - 1);

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

std::pair<int, int> MinesweeperBoard::getBoardSize(){
    return this -> BoardSize;
}

void MinesweeperBoard::setBoardSize(int x, int y){
    this -> BoardSize = {x, y};
}

void MinesweeperBoard::RevealTile(int x, int y){
    if(Grid[x][y].isRevealed){
        return;
    }
    Grid[x][y].isRevealed = true;
    if(Grid[x][y].isMine){
        this -> isGameOver = true;
        return;
    }
    this -> RevealedTiles++;
    Grid[x][y].neighborMines = this -> CalculateNeighborMines(x, y);

    if(Grid[x][y].neighborMines == 0){
        for(int h=std::max(x-1, 0); h<=std::min(x+1, this -> BoardSize.first-1); h++){
            for(int v=std::max(y-1, 0); v<=std::min(y+1, this -> BoardSize.second-1); v++){
                if(!this -> Grid[h][v].isRevealed){
                    this -> RevealTile(h,v);
                }
            }
        }
    }

    if(RevealedTiles >= this -> BoardSize.first * this -> BoardSize.second - TotalMines){
        this -> isGameWon = true;
    }
}

int MinesweeperBoard::CalculateNeighborMines(int x, int y){
    int MineCount=0;
    for(int h=std::max(x-1, 0); h<=std::min(x+1, this -> BoardSize.first-1); h++){
        for(int v=std::max(y-1, 0); v<=std::min(y+1, this -> BoardSize.second-1); v++){
            if(this -> Grid[h][v].isMine){
                MineCount++;
            }
        }
    }
    return MineCount;
}

void MinesweeperBoard::ToggleFlagTile(int x, int y){
    this -> Grid[x][y].isFlagged = !this -> Grid[x][y].isFlagged;
    if(Grid[x][y].isFlagged){
        this -> RemainingMines--;
    }
    else{
        this -> RemainingMines++;
    }
}