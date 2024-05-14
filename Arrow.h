#ifndef ARROW_H
#define ARROW_H

#include "Bullet.h"

class Arrow : public Bullet {

public:
    Arrow(int aim, Game* game, int power, int player = 1) : Bullet(aim, game, power, player) {}
    void specialEffect(Enemy* &enemy);
};

#endif // ARROW_H
