#include"Bullet.h"

#include <QGraphicsScene>
#include <QTimer>
#include <QList>
#include <cmath>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "PowerUp.h"
#include "Enemy.h"

Bullet::Bullet(int thisAim, Game* thisGame, int thisPower):QObject(), QGraphicsPixmapItem()
{ /*std::vector<QGraphicsPixmapItem> photos;*/

    QPixmap pix = QPixmap(":/images/circle.png");
    QPixmap scaledPixmap = pix.scaled(120, 75);
    setPixmap(scaledPixmap);
    this->setVisible(true);

    aim = thisAim;
    game = thisGame;
    power = thisPower;

    if(audio)
    {
        QMediaPlayer *bulletMedia;
        QAudioOutput *bulletOutput;
        bulletOutput= new QAudioOutput();
        bulletOutput -> setVolume (50);
        bulletMedia = new QMediaPlayer ();
        bulletMedia->setAudioOutput(bulletOutput);
        bulletMedia ->setSource(QUrl("qrc:/new/prefix1/bullet.mp3"));
        bulletMedia ->play();
    }

    moveTimer = new QTimer();
    connect(moveTimer, SIGNAL(timeout()),this,SLOT (move()));
    moveTimer->start(10);
}

void Bullet:: move()
{
    if(game->powerUp != nullptr && (x() + 25 >= game->powerUp->getX() && x() <= game->powerUp->getX() + 25) && (y() + 25 >= game->powerUp->getY() && y() <= game->powerUp->getY() + 25))
    {
        game->hitPowerUp();
    }

    for(int i = 0; i < game->enemies.size(); i++)
    {
        if((x() + 25 >= game->enemies[i]->getX() && x() <= game->enemies[i]->getX() + 50) && (y() + 25 >= game->enemies[i]->getY() && y() <= game->enemies[i]->getY() + 50))
        {
            scene()->removeItem(this);
            Enemy* e = game->enemies[i];
            if (!e->damageThis(power))
            { specialEffect(e); }
            else {

                delete this;
            }
            return;
        }
    }

    setPos((x() + (aim/2.0)), (y() + (20-abs(aim))/2.0));
    if(y()>800)
    {
        scene()->removeItem(this);
        delete this;
    }
}

void Bullet::specialEffect(Enemy* &e)
{
    delete this;
}
