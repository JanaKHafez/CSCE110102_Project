#ifndef CLANCASTLE_H
#define CLANCASTLE_H

#include "GameObject.h"

class Game;

class ClanCastle: public GameObject {

private:
    Game* game;

public:
    static int castleCount;
    static int castleCount2;
    ClanCastle(int thisX, int thisY, Game* thisGame, int player = 1);
    void breakObject();
};

#endif
