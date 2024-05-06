#include "Canon.h"
#include "Bullet.h"

#include <QMediaPlayer>
#include <QAudioOutput>

void Canon::shoot()
{
    if(allowShoot)
    {
        if(shootTimer != nullptr)
        {
            delete shootTimer;
        }

        Bullet * bullet = new Bullet(aim, game, power);
        bullet->setPos(x+35,y+35);
        scene()->addItem(bullet);
        allowShoot = false;

        shootTimer = new QTimer();
        connect(shootTimer, &QTimer::timeout, this, &Defence::letShoot);
        shootTimer->start(1000);
        QMediaPlayer *bulletMedia;
        QAudioOutput *bulletOutput;
        bulletOutput= new QAudioOutput();
        bulletOutput -> setVolume (50);
        bulletMedia = new QMediaPlayer ();
        bulletMedia->setAudioOutput(bulletOutput);
        bulletMedia ->setSource(QUrl("qrc:/new/prefix1/bullet.mp3"));
        bulletMedia ->play();
    }
}
