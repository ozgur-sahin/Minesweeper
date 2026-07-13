#include "GameWindow.h"

GameWindow::GameWindow(QWidget *parent, int HSize, int VSize) : QWidget(parent)
{
    GameBoard = new MinesweeperBoard{5, 5};
    GameBoard->DrawBoardFull();
    // std::cout << "Board initialized...\n";
    this->resize(HSize, VSize);
    this->setWindowTitle("Minesweeper");

    QGridLayout *layout = new QGridLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    // std::cout << "Layout created...\n";

    int rowNo = 0;
    GameGrid.resize(5, std::vector<QPushButton *>(5));
    for (std::vector<QPushButton *> &row : GameGrid)
    {
        // std::cout << rowNo << std::endl;
        int colNo = 0;
        for (QPushButton *&tile : row)
        {
            tile = new QPushButton(this);
            tile->resize(80, 80);
            tile->setProperty("rowNo", rowNo);
            tile->setProperty("colNo", colNo);
            layout->addWidget(tile, rowNo, colNo);
            connect(tile, &QPushButton::clicked, this, &GameWindow::onButtonClicked);

            // std::cout << "Tile: " << rowNo << ", " << colNo << "\n";
            colNo++;
        }
        rowNo++;
    }
}

void GameWindow::onButtonClicked()
{
    std::cout << "The button was clicked!" << std::endl;
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());

    if (clickedButton)
    {
        std::cout << clickedButton->property("rowNo").toInt() << " " << clickedButton->property("colNo").toInt() << "\n";
        int rowNo = clickedButton->property("rowNo").toInt();
        int colNo = clickedButton->property("colNo").toInt();
        GameBoard->RevealTile(rowNo, colNo);
    }
    else
    {
        std::cout << "Bad button!\n";
    }
    std::cout << "Attempting to redraw board now...\n";
    ReDrawBoard();
}

void GameWindow::ReDrawBoard()
{
    std::cout << "Redrawing board now...\n";
    for (auto &row : GameGrid)
    {
        for (auto &tile : row)
        {
            // if (tile == nullptr)
            // {
            //     std::cout << "Tile is nullptr!\n";
            // }
            // else
            // {
            //     std::cout << "Tile is all good!\n";
            // }
            if (tile == nullptr)
            {
                int rowNo = tile->property("rowNo").toInt();
                int colNo = tile->property("colNo").toInt();
                std::cout << rowNo << " " << colNo << "\n";
                if (GameBoard->GetRevealedState(rowNo, colNo))
                {
                    if (GameBoard->GetIsMine(rowNo, colNo))
                    {
                        tile->setText("&x");
                    }
                    else
                    {
                        int neighborMines = GameBoard->GetNeighborMines(rowNo, colNo);
                        std::cout << neighborMines << "\n";
                        tile->setText(QString::number(neighborMines));
                    }
                }
            }
        }
    }
}

GameWindow::~GameWindow()
{
    delete GameBoard;
    std::cout << "Board deleted. Exiting game...\n";
}