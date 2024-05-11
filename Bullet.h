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
    Game* game;
    QTimer* moveTimer;

public:
    Bullet(int thisAim, Game* game, int power);
    virtual void specialEffect(Enemy* &enemy);

public slots:
    void move();

};

#endif // BULLET_H
