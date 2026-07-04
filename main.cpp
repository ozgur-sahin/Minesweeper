#include "Minesweeper.h"

#include <iostream>


#define BOARDSIZEX 5
#define BOARDSIZEY 5

int main(){
    MinesweeperBoard board = MinesweeperBoard(BOARDSIZEX, BOARDSIZEY);
    board.DrawBoardFull();
    // board.DrawBoardASCII();

    while (1){
        int selectedRow, selectedCol;
        std::cout << "Enter row number: ";
        std::cin >> selectedRow;
        std::cout << "Enter column number: ";
        std::cin >> selectedCol;
        if(selectedRow >= board.getBoardSize().first 
        || selectedCol >= board.getBoardSize().second
        || selectedRow<0
        || selectedCol<0){
            std::cout << "Invalid Choice\n";
        }
        else{
            board.RevealTile(selectedRow, selectedCol);
            board.DrawBoardASCII();
            if(board.GetGameOverState()){
                std::cout << "Game over :(\n";
                break;
            }
            else if(board.GetGameWonState()){
                std::cout << "Congratulations! You won!\n";
                break;
            }
        }
    }
    return 0;
}