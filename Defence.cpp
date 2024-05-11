#include "Defence.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTimer>



void Defence::rotateArrow()
{
    L->setRotation(aim*-1*4.5);
}

Defence::Defence (int thisX, int thisY, Game* thisGame)
{
    aim = 0;
    power = 25;
    allowShoot = true;
    shootTimer = nullptr;
    game = thisGame;
    x = thisX;
    y = thisY;
    type = 2;
    color = Qt::blue;
    QBrush blueBrush(color);
    setBrush(blueBrush);
    setPos(x, y);
    L = new QGraphicsLineItem();
}

void Defence::DisplayArrow()
{
    L->setLine(x+40, y, x+40, y+80);
    L->setTransformOriginPoint(x+40, y+40);
    QPen pen(Qt::red);
    pen.setWidth(10);
    L->setPen(pen);
    scene()->addItem(L);
}

void Defence::aimRight(){
    if(aim < 20)
    {
        aim += 0.5;
        rotateArrow();
    }
}

void Defence::aimLeft(){
    if(aim > -20)
    {
        aim += -0.5;
        rotateArrow();
    }
}

void Defence::letShoot()
{
    if(!allowShoot) {
        allowShoot = true;
    }
    else
    {
        delete shootTimer;
        shootTimer = nullptr;
    }
}

void Defence::increasePower(float p)
{
    if(audio)
    {
        QMediaPlayer *powerUpMedia;
        QAudioOutput *powerUpAudio;
        powerUpAudio= new QAudioOutput();
        powerUpAudio -> setVolume (100);
        powerUpMedia = new QMediaPlayer ();
        powerUpMedia->setAudioOutput(powerUpAudio);
        powerUpMedia ->setSource(QUrl("qrc:/new/prefix1/powerUp.mp3"));
        powerUpMedia ->play();
    }

    power += power*(p/100);
}
