#ifndef POTION_H
#define POTION_H\

#include "Bullet.h"

class Potion : public Bullet
{

private:
    Enemy* enemy;
    QTimer* damageTimer;
    int count;

public:
    Potion(int aim, Game* game, int power) : Bullet(aim, game, power) {}
    void specialEffect(Enemy* &enemy);

public slots:
    void damageEnemy();
};

#endif // POTION_H
