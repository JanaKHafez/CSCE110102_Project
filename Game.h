#ifndef GAME_H
#define GAME_H

#include "qmediaplayer.h"
#include <QGraphicsItem>
#include <QFile>
#include <QTextStream>
#include <QGraphicsScene>
#include <QWidget>
#include <QGraphicsView>
#include <vector>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QTimer>
#include <QGraphicsView>

class Defence;
class GameObject;
class Enemy;
class CitizenWorker;
class PowerUp;

extern bool audio;

class Game: public QGraphicsView {

private:
    QGraphicsTextItem* startMsg;
    QGraphicsTextItem* loseMsg;
    QGraphicsTextItem* winMsg;
    QGraphicsTextItem* enemyMsg;
    QGraphicsTextItem* powerUpMsg;
    QGraphicsTextItem* countdownMsg;
    QGraphicsTextItem* audioMsg;
    QGraphicsTextItem* restartMsg;
    QTimer* countdownTimer;
    QFile mapFile;
    int arrayOfMapN[10][10];
    bool started = false;
    bool freeze = true;
    int score;
    int level;
    float goal;
    int enemyTime;
    int enemyCount;
    int defenceType;
    int enemySpeed;
    int timePassed;


public:
    Defence* defence;
    PowerUp* powerUp;
    QGraphicsScene *scene;
    QGraphicsView *view;
    std::vector<GameObject*> map;
    std::vector<Enemy*> enemies;
    std::vector<CitizenWorker*> citizenWorkers;

    Game(int level, QWidget *parent =0);
    void gameOver();
    void win();
    void nextLevel();
    void restart();
    void hitPowerUp();
    void defeatEnemy(Enemy* e);
    void keyPressEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* event);
    ~Game();

public slots:
    void generateEnemy();
    void countdown();
    void generatePowerUp();
};

#endif // GAME_H
