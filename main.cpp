#include "Minesweeper.h"


int main(){
    MinesweeperBoard board = MinesweeperBoard(15, 20);
    board.DrawEmptyBoardASCII();
    return 0;
}