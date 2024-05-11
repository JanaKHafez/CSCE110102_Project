#ifndef DEFENCE_H
#define DEFENCE_H

#include <qstring.h>
#include "GameObject.h"
#include "powerUp.h"

class Game;

class Defence: public GameObject {

protected:
    float aim;
    float power;
    QGraphicsLineItem* L;
    void rotateArrow();
    Game* game;
    bool allowShoot;
    QTimer* shootTimer;

public:
    Defence (int thisX, int thisY, Game* game);
    void DisplayArrow();
    virtual void shoot() = 0;
    void aimRight();
    void aimLeft();
    void increasePower(float percentage);

public slots:
    void letShoot();
};

#endif // DEFENCE_H
