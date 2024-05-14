#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"

class Enemy: public Player {

private:
    QColor color;
    int damage;
    int speed;
    int angle;
    int i=0;
    int time=0;
    QTimer* enemyTimer;
    int moveBackCounter;
    bool animationStarted = false;
    bool knockbackStarted = false;

    std::vector<QPixmap> enemyPhotos;

    QPixmap pix2 = QPixmap(":/images/enemyAnimation1.png").scaled(80,80);
    QPixmap pix3 = QPixmap(":/images/enemyAnimation2.png").scaled(80,80);
    QPixmap pix4 = QPixmap(":/images/enemyAnimation3.png").scaled(80,80);
    QPixmap pix5 = QPixmap(":/images/enemyAnimation4.png").scaled(80,80);
    QPixmap pix6 = QPixmap(":/images/enemyAnimation5.png").scaled(80,80);
    QPixmap pix7 = QPixmap(":/images/enemyAnimation6.png").scaled(80,80);
    QPixmap pix8 = QPixmap(":/images/enemyAnimation7.png").scaled(80,80);

public slots:
    void millisecond();

public:
    Enemy(int thisX, int thisY, int speed, Game* game);
    void attackObject();
    void pause();
    void play();
    bool damageThis(float amount, int player);
    void knockBack(int angle);
    void move();
    GameObject* getNearest();
    void moveBack();
    void enemyMoveAnimation();
    ~Enemy();
};

#endif // ENEMY_H
