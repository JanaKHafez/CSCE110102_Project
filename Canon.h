#ifndef CANON_H
#define CANON_H

#include "Defence.h"

class Canon : public Defence {

public:
    Canon(int x, int y, Game* game) : Defence(x, y, game) {}
    void shoot();
};

#endif // CANON_H
