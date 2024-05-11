#include "Fence.h"
#include <QMediaPlayer>
#include <QAudioOutput>

Fence::Fence(int thisX, int thisY)
{
    x = thisX;
    y = thisY;
    type = 3;
    color = Qt::gray;
    QBrush grayBrush(color);

    QPixmap pix = QPixmap(":/images/file (1).png");
    QPixmap scaledPixmap = pix.scaled(80, 80);

    setPixmap(scaledPixmap);
    setPos(x, y);
}

Fence::~Fence(){

}

