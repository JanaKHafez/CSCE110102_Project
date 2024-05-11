#include "ArcherTower.h"
#include "Arrow.h"


void ArcherTower::shoot()
{
    if(allowShoot)
    {
        if(shootTimer != nullptr)
        {
            delete shootTimer;
        }

        Arrow * arrow = new Arrow(aim, game, power);
        arrow->setPos(x+35,y+35);
        scene()->addItem(arrow);
        allowShoot = false;

        shootTimer = new QTimer();
        connect(shootTimer, &QTimer::timeout, this, &Defence::letShoot);
        shootTimer->start(1000);

    }
}
