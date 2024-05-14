#include "Canon.h"
#include "Bullet.h"

Canon::Canon(int x, int y, Game* game, int p) : Defence(x, y, game, p)
{
    QColor thisColor(189,169,156,255);
    color = thisColor;
}

void Canon::DisplayPic()
{
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem();
    QPixmap pix = QPixmap(":/images/TOWER1.png");
    QPixmap scaledPixmap = pix.scaled(80, 80);
    item->setPixmap(scaledPixmap);
    item->setPos(x, y);
    scene()->addItem(item);
}

void Canon::shoot()
{
    if(allowShoot)
    {
        if(shootTimer != nullptr)
        {
            delete shootTimer;
        }

        Bullet * bullet = new Bullet(aim, game, power, player);
        bullet->setPos(x-2,y+8);
        scene()->addItem(bullet);
        allowShoot = false;

        shootTimer = new QTimer();
        connect(shootTimer, &QTimer::timeout, this, &Defence::letShoot);
        shootTimer->start(1000);
    }
}
