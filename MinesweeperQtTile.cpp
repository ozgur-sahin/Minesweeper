#include "MinesweeperQtTile.h"

void MinesweeperQtTile::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        emit leftclicked();
    }
    else if (e->button() == Qt::RightButton)
    {
        emit rightclicked();
    }

    QPushButton::mousePressEvent(e);
}

MinesweeperQtTile::MinesweeperQtTile(int r, int c, QWidget *parent) : QPushButton(parent)
{
    coord.rowNo = r;
    coord.colNo = c;
}

TileCoordinates MinesweeperQtTile::getTileCoordinates()
{
    return coord;
}