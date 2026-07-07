#include "Minesweeper.h"

#include <iostream>
#include <QApplication>
#include <QWidget>


#define BOARDSIZEX 5
#define BOARDSIZEY 5

// int main(){
//     MinesweeperBoard board = MinesweeperBoard(BOARDSIZEX, BOARDSIZEY);
//     board.DrawBoardFull();
//     // board.DrawBoardASCII();

//     while (1){
//         int selectedRow, selectedCol;
//         std::cout << "Enter row number: ";
//         std::cin >> selectedRow;
//         std::cout << "Enter column number: ";
//         std::cin >> selectedCol;
//         if(selectedRow >= board.getBoardSize().first 
//         || selectedCol >= board.getBoardSize().second
//         || selectedRow<0
//         || selectedCol<0){
//             std::cout << "Invalid Choice\n";
//         }
//         else{
//             board.RevealTile(selectedRow, selectedCol);
//             board.DrawBoardASCII();
//             if(board.GetGameOverState()){
//                 std::cout << "Game over :(\n";
//                 break;
//             }
//             else if(board.GetGameWonState()){
//                 std::cout << "Congratulations! You won!\n";
//                 break;
//             }
//         }
//     }
//     return 0;
// }



int main(int argc, char *argv[]) {
    // 1. Initialize the main Qt application manager loop
    QApplication app(argc, argv);

    // 2. Instantiate a basic, empty graphical desktop window widget
    QWidget window;

    // 3. Customize the window properties (Width, Height in pixels)
    window.resize(400, 400);
    window.setWindowTitle("Minesweeper");

    // 4. Force the operating system to render the window visually on screen
    window.show();

    // 5. Hand control over to the application engine loop. 
    // It keeps the window open until you click the native 'X' close button.
    return app.exec();
}
