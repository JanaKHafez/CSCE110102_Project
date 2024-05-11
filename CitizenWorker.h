#ifndef CITIZENWORKER_H
#define CITIZENWORKER_H

#include "Player.h"


class CitizenWorker : public Player {

private:
    int repair;

public slots:
    void move();

public:
    CitizenWorker(int thisX, int thisY, Game* game);
    GameObject* getNearest();
    void repairObject();
    ~CitizenWorker();
};

#endif // CITIZENWORKER_H


