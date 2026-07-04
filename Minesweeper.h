// #include <random>
#include <vector>
// #include <utility>
#define MINECOUNT 10

struct BoardTile{
    bool isMine = false;
    bool isRevealed = false;
    bool isFlagged = false;
    int neighborMines = 0;
};

class MinesweeperBoard{
    private:
        std::pair<int, int> BoardSize;
        std::vector<std::vector<BoardTile>> Grid;
        void InitializeMines(int);
        void setBoardSize(int, int);
        void initializeBoard();
        bool isGameOver = false;
        bool isGameWon = false;
        int CalculateNeighborMines(int, int);
        int TotalMines;
        int RemainingMines;
        int RevealedTiles = 0;


    public:
        MinesweeperBoard(int, int);
        void DrawBoardASCII();
        std::pair<int, int> getBoardSize();
        void RevealTile(int, int);
        bool GetGameOverState();
        void DrawBoardFull();
        void ToggleFlagTile(int, int);
        bool GetGameWonState();
    
};