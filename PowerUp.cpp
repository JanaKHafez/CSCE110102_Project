#include "powerup.h"
#include "Game.h"

PowerUp::PowerUp (Game* game, int thisX, int thisY) {

    g = game;
    x = thisX;
    y = thisY;

    QPixmap pix = QPixmap(":/images/file (2).png");
    QPixmap scaledPixmap = pix.scaled(50, 50);
    setPixmap(scaledPixmap);
    setPos(x, y);
    this->setVisible(true);

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
