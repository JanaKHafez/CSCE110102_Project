#ifndef PLAYER_H
#define PLAYER_H
#include <qstring.h>
#include <QGraphicsItem>
#include <QObject>
#include <QTimer>
#include <QWidget>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <vector>
#include "Game.h"
#include "GameObject.h"

class Player : public QObject, public QGraphicsPixmapItem {

protected:
    float health;
    float x;
    float y;
    int toX;
    int toY;
    int stepSize;
    bool reached;
    GameObject* item;
    Game* game;
    virtual GameObject* getNearest() = 0;

public:
    Player(int thisX, int thisY, Game* game);
    void updateItem();
    int getX();
    int getY();
};

#endif // PLAYER_H
