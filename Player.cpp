#include "Player.h"

Player::Player(int thisX, int thisY, Game* thisGame)
{

    health = 100;
    x = thisX;
    y = thisY;
    game = thisGame;
    reached = false;
}

void Player::updateItem()
{
    item = getNearest();
    if(item != nullptr)
    {
        toX = item->getX() + 10;
        toY = item->getY() + 10;
        if(x > toX)
        {
            toX +=50;
        }
        if(y > toY)
        {
            toY +=50;
        }
        else
        {
            toY -= 50;
        }
    }
    else
    {
        toX = -1;
        toY = -1;
    }
}

int Player::getX() {return x;}
int Player::getY() {return y;}
