#ifndef ARROW_H
#define ARROW_H

#include "Bullet.h"

class Arrow : public Bullet {

public:
    Arrow(int aim, Game* game, int power) : Bullet(aim, game, power) {}
    void specialEffect(Enemy* &enemy);
};

#endif // ARROW_H
