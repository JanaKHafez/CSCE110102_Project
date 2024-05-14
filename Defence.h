#ifndef DEFENCE_H
#define DEFENCE_H

#include <qstring.h>
#include "Game.h"
#include "GameObject.h"


class Defence: public GameObject {
Q_OBJECT
protected:
    float aim;
    float power;
    int player;
    QGraphicsLineItem* L;
    void rotateArrow();
    Game* game;
    bool allowShoot;
    QTimer* shootTimer;

public:
    Defence (int thisX, int thisY, Game* game, int player = 1);
    void DisplayArrow();
    virtual void shoot() = 0;
    virtual void DisplayPic() = 0;
    void aimRight();
    void aimLeft();
    void increasePower(float percentage);

public slots:
    void letShoot();
};

#endif // DEFENCE_H
