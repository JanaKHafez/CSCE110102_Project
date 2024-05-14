#include "ClanCastle.h"

#include "Game.h"

ClanCastle::ClanCastle(int thisX, int thisY, Game* thisGame, int p)
{
    player = p;
    game = thisGame;
    broken = false;
    x = thisX;
    y = thisY;
    type = 1;
    color = Qt::yellow;
    QBrush yellowBrush(color);

    if(p == 1) {castleCount ++;}
    else if(p == 2) {castleCount2++;}

    QPixmap pix = QPixmap(":/images/file.png");
    QPixmap scaledPixmap = pix.scaled(80, 80);
    photos.push_back(pix);

    setPixmap(scaledPixmap);
    setPos(x, y);

    QPixmap pix2 = QPixmap(":/images/castle 2.jpeg");
    QPixmap scaledPixmap2 = pix2.scaled(80, 80);
    photos.push_back(scaledPixmap2);

    QPixmap pix3 = QPixmap(":/images/castle 3.jpeg");
    QPixmap scaledPixmap3 = pix3.scaled(80, 80);
    photos.push_back(scaledPixmap3);

    QPixmap pix4 = QPixmap(":/images/castle 4.jpeg");
    QPixmap scaledPixmap4 = pix4.scaled(80, 80);
    photos.push_back(scaledPixmap4);
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
        if(player == 1)
        {
            castleCount--;
            if(castleCount <= 0)
            {
                game->gameOver(1);
            }
        }
        else if (player == 2)
        {
            castleCount2--;
            if(castleCount2 <= 0)
            {
                game->gameOver(2);
            }
        }
    }
}
