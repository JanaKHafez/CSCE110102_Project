#include "ClanCastle.h"

#include "Game.h"

ClanCastle::ClanCastle(int thisX, int thisY, Game* thisGame)
{
    castleCount ++;
    broken = false;
    x = thisX;
    y = thisY;
    type = 1;
    color = Qt::yellow;
    QBrush yellowBrush(color);
    QPixmap pix = QPixmap(":/images/file.png");
    QPixmap scaledPixmap = pix.scaled(80, 80);
    setPixmap(scaledPixmap);
    setPos(x, y);
    game = thisGame;
}

void ClanCastle::breakObject()
{
    if(!broken)
    {
        QBrush greenBrush(Qt::green);
        QPixmap pix = QPixmap(":/images/greenland.jpeg");
        QPixmap scaledPixmap = pix.scaled(80, 80);
        setPixmap(scaledPixmap);
        //setPixmap(QPixmap(":/../../Downloads/citzen.jpeg"));
        broken = true;
        castleCount--;
        if(castleCount <= 0)
        {
            game->gameOver();
        }
    }
}
