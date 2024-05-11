#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"

class Enemy: public Player {

private:
    int damage;
    QColor color;
    int speed;
    int angle;
    int moveBackCounter;
    QTimer* moveTimer;
    QTimer* knockBackTimer;
     QTimer* MoveAnimationTimer;
    int i=0;
     std::vector<QPixmap> enemyPhotos;
     bool AnimationTimerStarted = false;



     QPixmap pix2 = QPixmap(":/images/enemyAnimation1.png").scaled(80,80);
     QPixmap pix3 = QPixmap(":/images/enemyAnimation2.png").scaled(80,80);
     QPixmap pix4 = QPixmap(":/images/enemyAnimation3.png").scaled(80,80);
     QPixmap pix5 = QPixmap(":/images/enemyAnimation4.png").scaled(80,80);
     QPixmap pix6 = QPixmap(":/images/enemyAnimation5.png").scaled(80,80);
     QPixmap pix7 = QPixmap(":/images/enemyAnimation6.png").scaled(80,80);
     QPixmap pix8 = QPixmap(":/images/enemyAnimation7.png").scaled(80,80);




public slots:
    void move();
    GameObject* getNearest();
    void moveBack();
    void enemyMoveAnimation();

public:
    Enemy(int thisX, int thisY, int speed, Game* game);
    void attackObject();
    bool damageThis(float amount);
    void knockBack(int angle);
    ~Enemy();
};

#endif // ENEMY_H
