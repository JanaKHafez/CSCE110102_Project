#include "Fence.h"
#include <QMediaPlayer>
#include <QAudioOutput>

Fence::Fence(int thisX, int thisY, int p)
{
    player = p;
    x = thisX;
    y = thisY;
    type = 3;
    color = Qt::gray;
    QBrush grayBrush(color);

    QPixmap pix = QPixmap(":/images/file (1).png");
    QPixmap scaledPixmap = pix.scaled(80, 80);
    photos.push_back(pix);

    setPixmap(scaledPixmap);
    setPos(x, y);

    QPixmap pix2 = QPixmap(":/images/fence2.jpeg");
    QPixmap scaledPixmap2 = pix2.scaled(80, 80);
    photos.push_back(scaledPixmap2);

    QPixmap pix3 = QPixmap(":/images/fence3.jpeg");
    QPixmap scaledPixmap3 = pix3.scaled(80, 80);
    photos.push_back(scaledPixmap3);

    QPixmap pix4 = QPixmap(":/images/fence4.jpeg");
    QPixmap scaledPixmap4 = pix4.scaled(80, 80);
    photos.push_back(scaledPixmap4);
}

Fence::~Fence(){

}

