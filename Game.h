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
#include <QGraphicsPixmapItem>

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
    QGraphicsTextItem* scoreMsg;
    QGraphicsTextItem* score2Msg;
    QGraphicsTextItem* powerUpMsg;
    QGraphicsTextItem* countdownMsg;
    QGraphicsPixmapItem* audioPicON;
    QGraphicsPixmapItem* audioPicOFF;
    QGraphicsPixmapItem* pausePic;
    QGraphicsPixmapItem* playPic;
    QTimer* gameTimer;
    QFile mapFile;
    int arrayOfMapN[10][10];
    bool started = false;
    bool freeze = true;
    bool paused = false;
    bool over = false;
    int score;
    int score2;
    int level;
    float goal;
    int enemyTime;
    int enemyCount;
    int defenceType;
    int enemySpeed;
    int time = 0;
    void end();

public:
    Defence* defence = nullptr;
    Defence* defence2;
    PowerUp* powerUp;
    QGraphicsScene *scene;
    QGraphicsView *view;
    std::vector<GameObject*> map;
    std::vector<Enemy*> enemies;
    std::vector<CitizenWorker*> citizenWorkers;

    Game( int level = 1, QWidget *parent = 0);
    void gameOver(int player);
    void win();
    void nextLevel();
    void restart();
    void hitPowerUp();
    void defeatEnemy(Enemy* enemey, int player = 1);
    void pause();
    void play();
    void keyPressEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void generatePowerUp();
    void generateEnemy();
    ~Game();

public slots:
    void millisecond();
};

#endif // GAME_H
