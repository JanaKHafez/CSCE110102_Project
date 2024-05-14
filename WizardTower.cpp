#include "WizardTower.h"
#include "Potion.h"

WizardTower::WizardTower(int x, int y, Game* game, int p): Defence(x, y, game, p)
{
    QColor thisColor(93,68,122,255);
    color = thisColor;
}

void WizardTower::DisplayPic()
{
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem();
    QPixmap pix = QPixmap(":/images/TOWER2.png");
    QPixmap scaledPixmap = pix.scaled(80, 80);
    item->setPixmap(scaledPixmap);
    item->setPos(x, y);
    scene()->addItem(item);
}

void WizardTower::shoot()
{
    if(allowShoot)
    {
        if(shootTimer != nullptr)
        {
            delete shootTimer;
        }

        Potion * potion = new Potion(aim, game, power);
        potion->setPos(x-2,y+8);
        scene()->addItem(potion);
        allowShoot = false;

        shootTimer = new QTimer();
        connect(shootTimer, &QTimer::timeout, this, &Defence::letShoot);
        shootTimer->start(1000);
    }
}
