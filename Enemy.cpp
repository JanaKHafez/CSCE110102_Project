#include "Enemy.h"

#include "CitizenWorker.h"

void Enemy::move()
{
    if(toX != -1 && toY != -1)
    {
        reached = true;
        if(abs(y-toY) > stepSize)
        {
            if(y > toY) {y += stepSize * -1;}
            else {y += stepSize;}
            reached = false;
        }

        if(abs(x-toX) > stepSize)
        {
            if(x > toX) {x += stepSize*-1;}
            else {x += stepSize;}
            reached = false;
        }

        if(!reached) {
            setPos(x, y);
        }

        QList collidingItems = this->collidingItems();
        for(int i = 0; i < collidingItems.size(); i++)
        {
            if(typeid(*(collidingItems[i])) == typeid(CitizenWorker))
            {
                scene()->removeItem(collidingItems[i]);
                delete collidingItems[i];
            }
        }
    }
    else {reached = false;}
}

Enemy::Enemy(int thisX, int thisY, int s, Game* game) : Player(thisX, thisY, game)
{
    if(game != nullptr)
    {
        speed = s;
        color = Qt::red;
        QBrush brush(color);
        setRect(0, 0, 20, 20);
        setBrush(brush);
        setPos(x, y);
        damage = 25;
        Player::updateItem();
        moveTimer = new QTimer();
        connect(moveTimer, &QTimer::timeout, this, &Enemy::move);
        moveTimer->start(speed);
        QTimer* attackTimer = new QTimer();
        connect(attackTimer, &QTimer::timeout, this, &Enemy::attackObject);
        attackTimer->start(1750);
        stepSize = 2;
    }
}

void Enemy::attackObject()
{
    if(reached && item != nullptr)
    {
        item->damage(damage);
        updateItem();
    }
}

GameObject* Enemy::getNearest()
{
    int minDiff = INT_MAX;
    int thisDiff;
    GameObject* item = nullptr;
    for(unsigned long long i = 0; i < game->map.size(); i++)
    {
        if((game->map)[i]->isBroken() == false && (game->map)[i]->getType() != 2)
        {
            int thisX = (game->map)[i]->getX();
            int thisY = (game->map)[i]->getY();
            int Xdiff = abs(x - thisX);
            int Ydiff = abs(y - thisY);
            thisDiff = Xdiff + Ydiff;
            if(thisDiff < minDiff)
            {
                minDiff = thisDiff;
                item = (game->map)[i];
            }
        }
    }
    return item;
    //find shortest path to a clan castle:
        //shortest path to every clan castle: HOW USING DIJKESTRA??
            //Create graph
        //find min
    //return first item in path
}

bool Enemy::damageThis(float amount)
{
    health -= amount;
    color = color.darker(100 + amount);
    QBrush brush(color);
    setBrush(brush);
    if(health <= 0)
    {
        scene()->removeItem(this);
        game->defeatEnemy(this);
        //enemy dying sound effect

        delete this;
        return true;
    }
    return false;
}

void Enemy::knockBack(int thisAngle)
{
    angle = thisAngle;
    moveBackCounter = 0;
    if(moveTimer != nullptr) {
        delete moveTimer;
        moveTimer = nullptr;
    }
    reached = false;
    knockBackTimer = new QTimer();
    connect(knockBackTimer, &QTimer::timeout, this, &Enemy::moveBack);
    knockBackTimer->start(speed);
}

void Enemy::moveBack()
{
    moveBackCounter ++;
    if(moveBackCounter * speed <= 1000)
    {
        x += stepSize * angle/20.0;
        y += stepSize * abs((20-angle)/20.0);
        setPos(x, y);
    }
    else
    {
        delete knockBackTimer;
        knockBackTimer = nullptr;
        if(moveTimer == nullptr)
        {
            moveTimer = new QTimer();
            connect(moveTimer, &QTimer::timeout, this, &Enemy::move);
            moveTimer->start(speed);
        }
    }
}

Enemy::~Enemy()
{}
