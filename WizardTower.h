#ifndef WIZARDTOWER_H
#define WIZARDTOWER_H

#include "Defence.h"

class WizardTower : public Defence {

public:
    WizardTower(int x, int y, Game* game, int p = 1);
    void DisplayPic();
    void shoot();
};

#endif // WIZARDTOWER_H
