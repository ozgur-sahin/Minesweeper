#include "GameWindow.h"

GameWindow::GameWindow(Config *config, QWidget *parent) : QWidget(parent)
{
    conf = config;
    int HSize = conf->qtconf.windowSize[0];
    int VSize = conf->qtconf.windowSize[1];
    int *tileSize = conf->qtconf.tileSize;

    GameBoard = new MinesweeperBoard{&conf->msconf};
    GameBoard->DrawBoardFull();
    this->resize(HSize, VSize);
    this->setWindowTitle("Minesweeper");

    GenerateTileLayout();
}

void GameWindow::GenerateTileLayout()
{
    QGridLayout *layout = new QGridLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    layout->setSizeConstraint(QLayout::SetFixedSize);
    // std::cout << "Layout created...\n";

    int rowNo = 0;
    GameGrid.resize(conf->msconf.GameBoardSize.row, std::vector<MinesweeperQtTile *>(conf->msconf.GameBoardSize.col));
    for (std::vector<MinesweeperQtTile *> &row : GameGrid)
    {
        // std::cout << rowNo << std::endl;
        int colNo = 0;
        for (MinesweeperQtTile *&tile : row)
        {
            tile = new MinesweeperQtTile(rowNo, colNo, this);
            // tile->resize(tileSize[0], tileSize[1]);
            layout->addWidget(tile, rowNo, colNo);
            tile->setText(" ");
            connect(tile, &MinesweeperQtTile::leftclicked, this, &GameWindow::onLeftClick);
            connect(tile, &MinesweeperQtTile::rightclicked, this, &GameWindow::onRightClick);

            // 1. Force the layout engine to freeze BOTH horizontal and vertical metrics
            tile->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

            // 2. Lock down the exact dimensions
            tile->setFixedSize(80, 80);

            // std::cout << "Tile: " << rowNo << ", " << colNo << "\n";
            colNo++;
        }
        rowNo++;
    }

    // Explicitly force the layout manager to respect the 80px grid boundaries
    for (int row = 0; row < conf->msconf.GameBoardSize.row; ++row)
    {
        layout->setRowMinimumHeight(row, 80);
    }

    for (int col = 0; col < conf->msconf.GameBoardSize.col; ++col)
    {
        layout->setColumnMinimumWidth(col, 80);
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
    if (GameBoard->GetGameOverState())
    {
        onGameOver();
        return;
    }
    if (GameBoard->GetGameWonState())
    {
        onGameWin();
        return;
    }
}

void GameWindow::onRightClick()
{
    // std::cout << "Button was right clicked!\n";

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

void GameWindow::DisableAllTiles()
{
    for (auto &row : GameGrid)
    {
        for (auto &tile : row)
        {
            tile->setDisabled(true);
        }
    }
}

void GameWindow::onGameOver()
{
    std::cout << "Game over :(\n";
    DisableAllTiles();
}

void GameWindow::onGameWin()
{
    std::cout << "Congratulations! You won!\n";
    DisableAllTiles();
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
                        // std::cout << neighborMines << "\n";
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