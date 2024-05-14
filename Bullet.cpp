#include"Bullet.h"

#include <QGraphicsScene>
#include <QTimer>
#include <QList>
#include <cmath>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "PowerUp.h"
#include "Enemy.h"

extern int mode;

Bullet::Bullet(int thisAim, Game* thisGame, int thisPower, int p):QObject(), QGraphicsPixmapItem()
{ /*std::vector<QGraphicsPixmapItem> photos;*/
    QPixmap pix = QPixmap(":/images/circle.png");
    QPixmap scaledPixmap = pix.scaled(120, 75);
    setPixmap(scaledPixmap);
    this->setVisible(true);

    aim = thisAim;
    game = thisGame;
    power = thisPower;
    player = p;

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

int Bullet:: move()
{
    if(game->powerUp != nullptr && (x() + 25 >= game->powerUp->getX() && x() <= game->powerUp->getX() + 25) && (y() + 25 >= game->powerUp->getY() && y() <= game->powerUp->getY() + 25))
    {
        game->hitPowerUp();
    }

    for(int i = 0; i < game->enemies.size(); i++)
    {
        if((x() + 25 >= game->enemies[i]->getX() && x() <= game->enemies[i]->getX() + 50) && (y() + 25 >= game->enemies[i]->getY() && y() <= game->enemies[i]->getY() + 50))
        {
            game->scene->removeItem(this);
            Enemy* e = game->enemies[i];
            if (!e->damageThis(power, player))
            { specialEffect(e); }
            else {

                delete this;
            }
            return 1;
        }
    }

    if(mode == 2)
    {
        for(int i = 0; i < game->map.size(); i++)
        {
            if((game->map[i]->getPlayer() != player && game->map[i]->getType() != 2 && ! game->map[i]->isBroken()) && ((x() + 30 >= game->map[i]->getX() && x() <= game->map[i]->getX() + 52) && (y() + 20 >= game->map[i]->getY() && y() <= game->map[i]->getY() + 80)))
            {
                game->scene->removeItem(this);
                game->map[i]->damage(power);
                delete this;
                return 2;
            }
        }
    }

    if(player == 1) {setPos((x() + (aim/2.0)), (y() + (20-abs(aim))/2.0));}
    else if(player == 2) {setPos((x() + (aim/2.0)), (y() - (20-abs(aim))/2.0));}
    if(y()>800)
    {
        scene()->removeItem(this);
        delete this;
    }
    return 0;
}

void Bullet::specialEffect(Enemy* &e)
{
    delete this;
}
