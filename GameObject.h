#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsItem>
#include<QFile>
#include<QTextStream>
#include<QGraphicsScene>
#include<QWidget>
#include<QGraphicsView>
#include <QKeyEvent>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QTimer>
#include<QGraphicsPixmapItem>

extern bool audio;

class GameObject: public QObject, public QGraphicsPixmapItem{

protected:
    int player;
    float health;
    int x;
    int y;
    int type;
    bool broken;
    QColor color;
    std::vector<QPixmap> photos;

public:
    GameObject();
    int getX();
    int getY();
    int getPlayer();
    bool isBroken();
    bool isFixed();
    bool damage(float amount);
    bool repair(int amount);
    virtual void breakObject();
    int getType();
};

#endif // GAMEOBJECT_H
