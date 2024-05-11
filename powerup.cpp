#include "powerup.h"
#include "Game.h"

PowerUp::PowerUp (Game* game, int thisX, int thisY) {

    g = game;
    x = thisX;
    y = thisY;

    QBrush blueBrush(Qt::blue);

    setRect(0, 0, 20, 20);
    setBrush(blueBrush);
    setPos(x, y);

    QTimer* showTimer = new QTimer();
    connect(showTimer, &QTimer::timeout, this, &PowerUp::remove);
    showTimer->start(10000);
}

void PowerUp::remove()
{
    scene()->removeItem(this);
    g->powerUp = nullptr;
    delete this;
}

int PowerUp::getX() {return x;}
int PowerUp::getY() {return y;}


