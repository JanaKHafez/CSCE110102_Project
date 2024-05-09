#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"

class Enemy: public Player {

private:
    int damage;
    QColor color;
    int speed;
    int angle;
    int moveBackCounter;
    QTimer* moveTimer;
    QTimer* knockBackTimer;

public slots:
    void move();
    GameObject* getNearest();
    void moveBack();

public:
    Enemy(int thisX, int thisY, int speed, Game* game);
    void attackObject();
    bool damageThis(float amount);
    void knockBack(int angle);
    ~Enemy();
};

#endif // ENEMY_H
