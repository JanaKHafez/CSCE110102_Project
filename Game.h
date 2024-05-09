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
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QTimer>
#include <QGraphicsView>

class Defence;
class GameObject;
class Enemy;
class CitizenWorker;

class Game: public QGraphicsView {

private:
    QGraphicsTextItem* startMsg;
    QGraphicsTextItem* loseMsg;
    QGraphicsTextItem* winMsg;
    QGraphicsTextItem* enemyMsg;
    QGraphicsTextItem* powerUpMsg;
    QGraphicsTextItem* countdownMsg;
    Defence* defence;
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
    Game(int level, QWidget *parent =0);
    QGraphicsScene *scene;
    QGraphicsView *view;
    void gameOver();
    void win();
    void nextLevel();
    std::vector<GameObject*> map;
    std::vector<Enemy*> enemies;
    std::vector<CitizenWorker*> citizenWorkers;
    void keyPressEvent(QKeyEvent* event);
    void defeatEnemy(Enemy* e);
    ~Game();

public slots:
    void generateEnemy();
    void countdown();
};

#endif // GAME_H
