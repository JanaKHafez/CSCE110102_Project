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
    setBrush(grayBrush);
    setPos(x, y);
}

Fence::~Fence(){

}

