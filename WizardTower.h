#ifndef WIZARDTOWER_H
#define WIZARDTOWER_H

#include "Defence.h"

class WizardTower : public Defence {

public:
    WizardTower(int x, int y, Game* game) : Defence(x, y, game) {}
    void shoot();
};

#endif // WIZARDTOWER_H
