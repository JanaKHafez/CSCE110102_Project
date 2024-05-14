#include "CitizenWorker.h"

CitizenWorker::CitizenWorker(int thisX, int thisY, Game* game, int p) : Player(thisX, thisY, game)
{
    // QBrush whiteBrush(Qt::white);

    player = p;

    QPixmap pix = QPixmap(":/images/citzen (1) (1).png");
    QPixmap scaledPixmap = pix.scaled(50, 50);
    setPixmap(scaledPixmap);
    setPos(x, y);
    repair = 25;    
    stepSize = 20;

    photos.push_back(pix2);
    photos.push_back(pix3);
    photos.push_back(pix4);
    photos.push_back(pix5);
    photos.push_back(pix6);
    photos.push_back(pix7);

    repairPhotos.push_back(pix8);
    repairPhotos.push_back(pix9);
    repairPhotos.push_back(pix10);
    repairPhotos.push_back(pix11);

    Player::updateItem();

    citizenTimer = new QTimer;
    connect(citizenTimer, &QTimer::timeout, this, &CitizenWorker::millisecond);
    citizenTimer->start(100);

}

void CitizenWorker::millisecond()
{
    time+=100;

    if(time%100 == 0)
    {
        move();
    }

    if(time%1000 == 0)
    {
        repairObject();
    }

    if(time%100 == 0 && startMoveAnimation)
    {
        moveAnimation();
    }

    if(time%100 == 0 && startRepairAnimation)
    {
        repairAnimation();
    }
}

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

void CitizenWorker::moveAnimation()
{

    setPixmap(photos[i]);
    i++;
    if(i >= 6){i=0;}
}

void CitizenWorker::repairAnimation()
{
    setPixmap(repairPhotos[j]);
    j++;
    if(j >= 4){j=0;}
}

GameObject* CitizenWorker::getNearest()
{
    int minDiff = INT_MAX;
    int thisDiff;
    GameObject* item = nullptr;
    for(unsigned long long i = 0; i < game->map.size(); i++)
    {
        if((game->map)[i]->isBroken() == false && (game->map)[i]->isFixed() == false && (game->map)[i]->getPlayer() == player)
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

    if(item != nullptr && reached == false && !startMoveAnimation)
    {
        startRepairAnimation = false;
        startMoveAnimation = true;
    }

    return item;
}

void CitizenWorker::repairObject()
{
    if(reached && item != nullptr)
    {
        startMoveAnimation = false;
        startRepairAnimation = true;
        if(item->repair(25))
        {
            startRepairAnimation=false;
            startMoveAnimation=true;
        }
    }
    Player::updateItem();
}

void CitizenWorker::pause()
{
    delete citizenTimer;
}

void CitizenWorker::play()
{
    citizenTimer = new QTimer;
    connect(citizenTimer, &QTimer::timeout, this, &CitizenWorker::millisecond);
    citizenTimer->start(100);
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
