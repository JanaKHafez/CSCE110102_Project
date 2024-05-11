#ifndef DEFENCE_H
#define DEFENCE_H

#include <qstring.h>
#include "Game.h"
#include "GameObject.h"


class Defence: public GameObject {

protected:
    int aim;
    int power;
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
    void increasePower(int percentage);

public slots:
    void letShoot();
};

#endif // DEFENCE_H
