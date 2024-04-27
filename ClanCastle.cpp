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
    setBrush(yellowBrush);
    setPos(x, y);
    game = thisGame;
}

void ClanCastle::breakObject()
{
    if(!broken)
    {
        QBrush greenBrush(Qt::green);
        setBrush(greenBrush);
        broken = true;
        castleCount--;
        if(castleCount <= 0)
        {
            game->gameOver();
        }
    }
}
