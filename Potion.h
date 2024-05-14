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
    Potion(int aim, Game* game, int power, int player = 1) : Bullet(aim, game, power, player) {}
    void specialEffect(Enemy* &enemy);

public slots:
    void damageEnemy();
};

#endif // POTION_H
