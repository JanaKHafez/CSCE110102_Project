#include "Enemy.h"

#include "CitizenWorker.h"

Enemy::Enemy(int thisX, int thisY, int s, Game* game) : Player(thisX, thisY, game)
{
    if(game != nullptr)
    {
        stepSize = 10;
        damage = 25;

        enemyPhotos.push_back(pix2);
        enemyPhotos.push_back(pix3);
        enemyPhotos.push_back(pix4);
        enemyPhotos.push_back(pix5);
        enemyPhotos.push_back(pix6);
        enemyPhotos.push_back(pix7);
        enemyPhotos.push_back(pix8);

        speed = s;
        color = Qt::red;
        QBrush brush(color);
        QPixmap pix = QPixmap(":/images/enemyAnimation1.png");
        QPixmap scaledPixmap = pix.scaled(120, 120);

        setPixmap(scaledPixmap);
        setPixmap(scaledPixmap);
        setPos(x, y);

        Player::updateItem();

        enemyTimer = new QTimer();
        connect(enemyTimer, &QTimer::timeout, this, &Enemy::millisecond);
        enemyTimer->start(50);
    }
}

void Enemy::millisecond()
{
    time+=50;

    if(time%100 == 0 && !knockbackStarted)
    {
        animationStarted = true;
        enemyMoveAnimation();
    }

    if(time%speed == 0 && !knockbackStarted)
    {
        move();
    }

    if(time%1750 == 0)
    {
        attackObject();
    }

    if(time%speed == 0 && knockbackStarted)
    {
        moveBack();
    }
}

void Enemy::enemyMoveAnimation()
{
    setPixmap(enemyPhotos[i]);
    i++;
    if(i >= 7){i=0;}
}

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

void Enemy::attackObject()
{
    if(reached && item != nullptr)
    {
        item->damage(damage);
        Player::updateItem();
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

bool Enemy::damageThis(float amount, int p)
{
    health -= amount;
    color = color.darker(100 + amount);
    QBrush brush(color);
    // setBrush(brush);
    if(health <= 0)
    {
        scene()->removeItem(this);
        game->defeatEnemy(this, p);
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
    knockbackStarted = true;
    reached = false;
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
        knockbackStarted = false;
        updateItem();
    }
}

void Enemy::pause()
{
    delete enemyTimer;
}

void Enemy::play()
{
    enemyTimer = new QTimer();
    connect(enemyTimer, &QTimer::timeout, this, &Enemy::millisecond);
    enemyTimer->start(50);
}

Enemy::~Enemy()
{}
