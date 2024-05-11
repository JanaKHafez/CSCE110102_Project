#ifndef CITIZENWORKER_H
#define CITIZENWORKER_H

#include "Player.h"


class CitizenWorker : public Player {

private:
    int repair;
    int i = 0;
    int j = 0;
    bool AnimationTimerStarted = false;
    QTimer * repairTimerAnimation;
    QTimer * ti;
    std::vector<QPixmap> photos;
    std::vector<QPixmap> repairPhotos;

    QPixmap pix2 = QPixmap(":/images/citzenMoveanimation1.png").scaled(50,50);
    QPixmap pix3 = QPixmap(":/images/citzenMoveanimation2.png").scaled(50,50);
    QPixmap pix4 = QPixmap(":/images/citzenMoveanimation3.png").scaled(50,50);
    QPixmap pix5 = QPixmap(":/images/citzenMoveanimation4.png").scaled(50,50);
    QPixmap pix6 = QPixmap(":/images/citzenMoveanimation5.png").scaled(50,50);
    QPixmap pix7 = QPixmap(":/images/6.png").scaled(50,50);

    QPixmap pix8 = QPixmap(":/images/citzenWorkerRepairAnimation1.png").scaled(50,50);
    QPixmap pix9 = QPixmap(":/images/citzenWorkerRepairAnimation2.png").scaled(50,50);
    QPixmap pix10 = QPixmap(":/images/citzenWorkerRepairAnimation3.png").scaled(50,50);
    QPixmap pix11 = QPixmap(":/images/citzenWorkerRepairAnimation4.png").scaled(50,50);

public slots:
    void move();
    void moveAnimation();
    void repairAnimation();

public:
    CitizenWorker(int thisX, int thisY, Game* game);
    GameObject* getNearest();
    void repairObject();
    ~CitizenWorker();
};

#endif // CITIZENWORKER_H


