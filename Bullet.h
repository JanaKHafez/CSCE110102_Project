#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsItem>
#include <QObject>

#include "Game.h"
#include<QGraphicsPixmapItem>

class Bullet: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

protected:
    int aim;
    int power;
    int player;
    Game* game;
    QTimer* moveTimer;

public:
    Bullet(int thisAim, Game* game, int power, int player = 1);
    virtual void specialEffect(Enemy* &enemy);

public slots:
    int move();

};

#endif // BULLET_H
