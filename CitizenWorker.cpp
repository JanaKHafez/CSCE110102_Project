#include "CitizenWorker.h"

void CitizenWorker::move()
{
    if(toX != -1 && toY != -1)
    {
        reached = true;
        if(abs(y-toY) >= stepSize)
        {
            if(y > toY) {y += stepSize * -1;}
            else {y += stepSize;}
            reached = false;
        }

        if(abs(x-toX) >= stepSize)
        {
            if(x > toX) {x += stepSize*-1;}
            else {x += stepSize;}
            reached = false;
        }

        if(!reached) {setPos(x, y);}
    }
    else {reached = false;}
}

CitizenWorker::CitizenWorker(int thisX, int thisY, Game* game) : Player(thisX, thisY, game)
{

    QBrush whiteBrush(Qt::white);
    setRect(0, 0, 20, 20);
    setBrush(whiteBrush);
    setPos(x, y);
    repair = 25;
    QTimer* timerMove = new QTimer();
    updateItem();
    connect(timerMove, &QTimer::timeout, this, &CitizenWorker::move);
    timerMove->start(50);
    QTimer* timerRepair = new QTimer();
    connect(timerRepair, &QTimer::timeout, this, &CitizenWorker::repairObject);
    timerRepair->start(1000);
    stepSize = 20;
}

GameObject* CitizenWorker::getNearest()
{
    int minDiff = INT_MAX;
    int thisDiff;
    GameObject* item = nullptr;
    for(unsigned long long i = 0; i < game->map.size(); i++)
    {
        if((game->map)[i]->isBroken() == false && (game->map)[i]->isFixed() == false)
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
}

void CitizenWorker::repairObject()
{
    Player::updateItem();
    if(reached && item != nullptr)
    {
        item->repair(repair);
    }
}

CitizenWorker::~CitizenWorker()
{
    for(int i = 0; i < game->citizenWorkers.size(); i++)
    {
        if(this == game->citizenWorkers[i])
        {
            game->citizenWorkers.erase(game->citizenWorkers.begin()+i);
            return;
        }
    }
}