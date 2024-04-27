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


class GameObject: public QObject, public QGraphicsRectItem{

protected:
    int health;
    int x;
    int y;
    int type;
    bool broken;
    QColor color;

public:
    GameObject();
    int getX();
    int getY();
    bool isBroken();
    bool isFixed();
    bool damage(int amount);
    bool repair(int amount);
    virtual void breakObject();
    int getType();
};

#endif // GAMEOBJECT_H
