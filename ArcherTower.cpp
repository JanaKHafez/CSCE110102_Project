#include "ArcherTower.h"
#include "Arrow.h"

ArcherTower::ArcherTower(int x, int y, Game* game, int p) : Defence(x, y, game, p)
{
    QColor thisColor(244,235,213,255);
    color = thisColor;
}

void ArcherTower::DisplayPic()
{
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem();
    QPixmap pix = QPixmap(":/images/TOWER3.png");
    QPixmap scaledPixmap = pix.scaled(80, 80);
    item->setPixmap(scaledPixmap);
    item->setPos(x, y);
    scene()->addItem(item);
}

void ArcherTower::shoot()
{
    if(allowShoot)
    {
        if(shootTimer != nullptr)
        {
            delete shootTimer;
        }

        Arrow * arrow = new Arrow(aim, game, power);
        arrow->setPos(x-2,y+8);
        scene()->addItem(arrow);
        allowShoot = false;

        shootTimer = new QTimer();
        connect(shootTimer, &QTimer::timeout, this, &Defence::letShoot);
        shootTimer->start(1000);

    }
}
