#include <random>
#include <utility>

struct BoardTile{
    bool isMine;
    int position[2];
};

struct BoardSize{
    int xsize, ysize;
};

class MinesweeperBoard{
    private:
    BoardSize Size;
    std::vector<int[2]> MinePositions;
    void InitializeMines(int);

    public:
    MinesweeperBoard(int, int);
    void DrawEmptyBoardASCII();
    BoardSize getBoardSize();
    void setBoardSize(int, int);
};