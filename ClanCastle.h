#ifndef CLANCASTLE_H
#define CLANCASTLE_H

#include "GameObject.h"

class Game;

class ClanCastle: public GameObject {

private:
    Game* game;

public:
    static int castleCount;
    ClanCastle(int thisX, int thisY, Game* thisGame);
    void breakObject();
};

#endif
