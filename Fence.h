#ifndef FENCE_H
#define FENCE_H

#include "GameObject.h"


class Fence: public GameObject {

public:
    Fence(int thisX, int thisY, int player = 1);
    ~Fence ();

};

#endif // FENCE_H
