#include "GameObject.h"
#include <QMediaPlayer>
#include <QAudioOutput>

GameObject::GameObject() {
    health = 100;
    setScale(1);
    broken = false;
}

int GameObject::getX() {return x;}
int GameObject::getY() {return y;}
int GameObject::getPlayer() {return player;}

bool GameObject::isBroken()
{
    if(health <= 0) {

        return true;

    }
    else {
        return false;}
}

bool GameObject::isFixed()
{
    if(health == 100) {return true;}
    else {return false;}
}

bool GameObject::damage(float amount)
{
    if(!broken)
    {
        health = health - amount;
        color = color.darker(amount*5);
        QBrush newBrush(color);
         //setPixmap(QPixmap(":/../../Downloads/citzen.jpeg"));
        if(health <= 0)
        {
            breakObject();
            return true;
        }
        else if (health <= 25)
        {
            setPixmap(photos[3]);
        }
        else if (health <= 50)
        {
            setPixmap(photos[2]);
        }
        else if(health <= 75)
        {
            setPixmap(photos[1]);
        }
        return false;
    }
    return true;
}

bool GameObject::repair(int amount)
{
    if(!broken)
    {
        health += amount;
        color = color.lighter(amount*5);
        QBrush newBrush(color);
        //setPixmap(QPixmap(":/../../Downloads/citzen.jpeg"));
        if(health > 100)
        {
            health = 100;
            setPixmap(photos[0]);
            return true;
        }
        else if(health >= 75)
        {
            setPixmap(photos[0]);
        }
        else if(health >= 50)
        {
            setPixmap(photos[1]);
        }
        else if(health >= 25)
        {
            setPixmap(photos[2]);
        }
        else
        {
            setPixmap(photos[3]);
        }
        return false;
    }
    return false;
}

void GameObject::breakObject()
{
    QPixmap pix = QPixmap(":/images/greenland.jpeg");
    QPixmap scaledPixmap = pix.scaled(80, 80);
    setPixmap(scaledPixmap);
    QBrush greenBrush(Qt::green);
    //setPixmap(QPixmap(":/../../Downloads/citzen.jpeg"));

    if(audio)
    {
        QMediaPlayer *fenceMedia;
        QAudioOutput *fenceAudio;
        fenceAudio= new QAudioOutput();
        fenceAudio -> setVolume (50);
        fenceMedia = new QMediaPlayer ();
        fenceMedia->setAudioOutput(fenceAudio);
        fenceMedia ->setSource(QUrl("qrc:/new/prefix1/fenceDestroyed.mp3"));
        fenceMedia ->play();
    }
    broken = true;
}

int GameObject::getType() {return type;}
