#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsItem>
#include <QObject>

#include "Game.h"

class Bullet: public QObject, public QGraphicsRectItem {
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
