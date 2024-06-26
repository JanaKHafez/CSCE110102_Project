#ifndef POWERUP_H
#define POWERUP_H

#include <QObject>
#include <QGraphicsRectItem>

class Game;
class Defence;

class PowerUp : public QObject, public QGraphicsRectItem
{
protected :
    Game *g;
    Defence *d;
    int x;
    int y;

public:
    PowerUp(Game* game, int x, int y);
    int getX();
    int getY();

public slots:
    void remove();
};

#endif // POWERUP_H
