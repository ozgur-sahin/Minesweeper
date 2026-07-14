#include "GameWindow.h"

GameWindow::GameWindow(int HSize, int VSize, QWidget *parent) : QWidget(parent)
{
    GameBoard = new MinesweeperBoard{5, 5};
    GameBoard->DrawBoardFull();
    this->resize(HSize, VSize);
    this->setWindowTitle("Minesweeper");

    QGridLayout *layout = new QGridLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    // std::cout << "Layout created...\n";

    int rowNo = 0;
    GameGrid.resize(5, std::vector<MinesweeperQtTile *>(5));
    for (std::vector<MinesweeperQtTile *> &row : GameGrid)
    {
        // std::cout << rowNo << std::endl;
        int colNo = 0;
        for (MinesweeperQtTile *&tile : row)
        {
            tile = new MinesweeperQtTile(rowNo, colNo, this);
            tile->resize(80, 80);
            layout->addWidget(tile, rowNo, colNo);
            tile->setText(" ");
            connect(tile, &MinesweeperQtTile::leftclicked, this, &GameWindow::onLeftClick);
            connect(tile, &MinesweeperQtTile::rightclicked, this, &GameWindow::onRightClick);

            // std::cout << "Tile: " << rowNo << ", " << colNo << "\n";
            colNo++;
        }
        rowNo++;
    }
}

void GameWindow::onLeftClick()
{
    // std::cout << "The button was left clicked!" << std::endl;
    MinesweeperQtTile *clickedButton = qobject_cast<MinesweeperQtTile *>(sender());

    if (clickedButton)
    {
        TileCoordinates coord = clickedButton->getTileCoordinates();
        // std::cout << coord.rowNo << " " << coord.colNo << "\n";
        GameBoard->RevealTile(coord.rowNo, coord.colNo);
    }
    else
    {
        std::cout << "Bad button!\n";
    }
    ReDrawBoard();
}

void GameWindow::onRightClick()
{
    std::cout << "Button was right clicked!\n";

    MinesweeperQtTile *clickedButton = qobject_cast<MinesweeperQtTile *>(sender());

    if (clickedButton)
    {
        TileCoordinates coord = clickedButton->getTileCoordinates();
        // std::cout << coord.rowNo << " " << coord.colNo << "\n";
        GameBoard->ToggleFlagTile(coord.rowNo, coord.colNo);
    }
    else
    {
        std::cout << "Bad button!\n";
    }
    ReDrawBoard();
}

void GameWindow::ReDrawBoard()
{
    // std::cout << "Redrawing board now...\n";
    for (auto &row : GameGrid)
    {
        for (auto &tile : row)
        {
            if (tile)
            {
                TileCoordinates coord = tile->getTileCoordinates();
                if (GameBoard->GetRevealedState(coord.rowNo, coord.colNo))
                {
                    if (GameBoard->GetIsMine(coord.rowNo, coord.colNo))
                    {
                        tile->setText("&x");
                    }
                    else
                    {
                        int neighborMines = GameBoard->GetNeighborMines(coord.rowNo, coord.colNo);
                        std::cout << neighborMines << "\n";
                        tile->setText(QString::number(neighborMines));
                    }
                }
                else if (GameBoard->GetFlaggedState(coord.rowNo, coord.colNo))
                {
                    tile->setText("&F");
                }
                else
                {
                    tile->setText("");
                }
            }
            else
            {
                std::cerr << "Tile is nullptr!\n";
            }
        }
    }
}

GameWindow::~GameWindow()
{
    for (auto &row : GameGrid)
    {
        for (auto &tile : row)
        {
            delete tile;
        }
    }
    std::cout << "All tiles deleted\n";
    delete GameBoard;
    std::cout << "Board deleted. Exiting game...\n";
}