#include "Potion.h"
#include "Enemy.h"

void Potion::specialEffect(Enemy* &e) {
    count = 0;
    enemy = e;
    delete moveTimer;
    damageTimer = new QTimer();
    connect(damageTimer, &QTimer::timeout, this, &Potion::damageEnemy);
    damageTimer->start(1000);
}

void Potion::damageEnemy()
{
    count ++;
    if(count <= 3)
    {
        for(int i = 0; i < game->enemies.size(); i++)
        {
            if( game->enemies[i] == enemy)
            {
                enemy->damageThis(12.5, player);
                return;
            }
        }
    }
    else
    {
        delete damageTimer;
        delete this;
    }
}
