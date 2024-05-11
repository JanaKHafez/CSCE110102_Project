#ifndef ARCHERTOWER_H
#define ARCHERTOWER_H

#include "Defence.h"

class ArcherTower : public Defence {

public:
    ArcherTower(int x, int y, Game* game);
    void DisplayPic();
    void shoot();
};

#endif // ARCHERTOWER_H
