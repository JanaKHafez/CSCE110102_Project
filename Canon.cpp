#include "Canon.h"
#include "Bullet.h"

void Canon::shoot()
{
    if(allowShoot)
    {
        if(shootTimer != nullptr)
        {
            delete shootTimer;
        }

        Bullet * bullet = new Bullet(aim, game, power);
        bullet->setPos(x+35,y+35);
        scene()->addItem(bullet);
        allowShoot = false;

        shootTimer = new QTimer();
        connect(shootTimer, &QTimer::timeout, this, &Defence::letShoot);
        shootTimer->start(1000);
    }
}
