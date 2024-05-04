#ifndef GAME_H
#define GAME_H

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
    int score;
    int arrayOfMapN[10][10];
    Defence* defence;
    bool started = false;
    int level;
    int goal;
    int enemyTime;
    int enemyCount;
    int defenceType;
    bool freeze;

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
};

#endif // GAME_H
