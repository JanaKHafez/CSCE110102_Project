#include "Arrow.h"
#include "Enemy.h"

void Arrow::specialEffect(Enemy* &enemy) {
    enemy->knockBack(aim, player);
    delete this;
}
