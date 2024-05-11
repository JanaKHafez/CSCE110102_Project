#include "WizardTower.h"
#include "Potion.h"

void WizardTower::shoot()
{
    if(allowShoot)
    {
        if(shootTimer != nullptr)
        {
            delete shootTimer;
        }

        Potion * potion = new Potion(aim, game, power);
        potion->setPos(x+35,y+35);
        scene()->addItem(potion);
        allowShoot = false;

        shootTimer = new QTimer();
        connect(shootTimer, &QTimer::timeout, this, &Defence::letShoot);
        shootTimer->start(1000);
    }
}
