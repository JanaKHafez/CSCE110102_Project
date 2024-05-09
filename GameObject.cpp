#include "GameObject.h"
#include <QMediaPlayer>
#include <QAudioOutput>

GameObject::GameObject() {
    health = 100;
    setRect(0, 0, 80, 80);
    broken = false;
}

int GameObject::getX() {return x;}
int GameObject::getY() {return y;}

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

bool GameObject::damage(int amount)
{
    if(!broken)
    {
        health = health - amount;
        color = color.darker(amount*5);
        QBrush newBrush(color);
        setBrush(newBrush);
        if(health <= 0)
        {
            breakObject();
            return true;
        }
        else {return false;}
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
        setBrush(newBrush);
        if(health > 100) {health = 100; return true;}
        return false;
    }
    return false;
}

void GameObject::breakObject()
{
    QBrush greenBrush(Qt::green);
    setBrush(greenBrush);
    QMediaPlayer *fenceMedia;
    QAudioOutput *fenceAudio;
    fenceAudio= new QAudioOutput();
    fenceAudio -> setVolume (50);
    fenceMedia = new QMediaPlayer ();
    fenceMedia->setAudioOutput(fenceAudio);
    fenceMedia ->setSource(QUrl("qrc:/new/prefix1/fenceDestroyed.mp3"));
    fenceMedia ->play();
    broken = true;
}

int GameObject::getType() {return type;}
