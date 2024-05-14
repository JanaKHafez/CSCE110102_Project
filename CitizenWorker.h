#ifndef CITIZENWORKER_H
#define CITIZENWORKER_H

#include "Player.h"


class CitizenWorker : public Player {

private:
    int player;
    int repair;
    int i = 0;
    int j = 0;
    int time = 0;
    bool startMoveAnimation = false;
    bool startRepairAnimation = false;
    QTimer* citizenTimer;
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
    void millisecond();

public:
    CitizenWorker(int thisX, int thisY, Game* game, int player = 1);
    GameObject* getNearest();
    void move();
    void moveAnimation();
    void repairAnimation();
    void repairObject();
    void pause();
    void play();
    ~CitizenWorker();
};

#endif // CITIZENWORKER_H


