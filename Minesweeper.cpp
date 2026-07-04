#include <iostream>
#include "Minesweeper.h"

MinesweeperBoard::MinesweeperBoard(int x, int y){
    this -> setBoardSize(x, y);
    // std::cout << "x=" << xsize << ", y=" << ysize << "\n";
}

void MinesweeperBoard::DrawEmptyBoardASCII(){
    for(int i=0; i < Size.xsize; i++){
        for(int j=0; j < Size.ysize; j++){
            std::cout << "*";
        }
        std::cout << "\n";
    }
}

void MinesweeperBoard::InitializeMines(int minecount){

}

BoardSize MinesweeperBoard::getBoardSize(){
    return this -> Size;
}

void MinesweeperBoard::setBoardSize(int x, int y){
    this -> Size.xsize = x;
    this -> Size.ysize = y;
}