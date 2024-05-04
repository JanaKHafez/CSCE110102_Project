#include"Game.h"

#include <QTextStream>
#include <QString>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QGraphicsView>
#include <QtAssert>
#include <QTimer>
#include <qapplication.h>
#include <stdlib.h>
#include "Enemy.h"
#include "ClanCastle.h"
#include "Canon.h"
#include "ArcherTower.h"
#include "WizardTower.h"
#include "Fence.h"
#include "CitizenWorker.h"

extern Game* game;

Game::Game(int thisLevel, QWidget* parent) : QGraphicsView(parent) {

    score = 0;
    freeze = true;

    level = thisLevel;

    switch (level)
    {
    case 1: {
        winTime = 60000;
        enemyTime = 15000;
        enemyCount = 2;
        defenceType = 1;
        break;
    }
    case 2: {
        winTime = 60000;
        enemyTime = 20000;
        enemyCount = 3;
        defenceType = 2;
        break;
    }
    case 3: {
        winTime = 60000;
        enemyTime = 20000;
        enemyCount = 4;
        defenceType = 3;
        break;
    }
    case 4: {
        winTime = 60000;
        enemyTime = 15000;
        enemyCount = 3;
        defenceType = 2;
        break;
    }
    case 5: {
        winTime = 60000;
        enemyTime = 20000;
        enemyCount = 5;
        defenceType = 3;
        break;
    }

    }

    winMsg = new QGraphicsTextItem(QString("You Win!!!"));loseMsg = new QGraphicsTextItem(QString("You Lose!"));
    enemyMsg = new QGraphicsTextItem(QString("Score: ") + QString::number(score));
    powerUpMsg = new QGraphicsTextItem(QString("Power Up!"));
    if(level == 1) {startMsg = new QGraphicsTextItem(QString("Level ") + QString::number(level) + "\n" + QString("Press space to start"));}
    else {startMsg = new QGraphicsTextItem(QString("Level ") + QString::number(level -1) + QString(" Completed!") + "\n" + QString("Level ") + QString::number(level) + "\n" + QString("Press space to start"));}

    QFont fontBig;
    QFont fontSmall;
    QColor colorWhite(Qt::white);
    QColor colorRed(Qt::red);
    fontBig.setPointSize(60);
    fontSmall.setPointSize(16);

    startMsg -> setFont(fontBig);
    startMsg -> setDefaultTextColor(colorWhite);
    startMsg -> setPos(0, 400);

    loseMsg -> setFont(fontBig);
    loseMsg -> setDefaultTextColor(colorRed);
    loseMsg -> setPos(0, 500);

    winMsg -> setFont(fontBig);
    winMsg -> setDefaultTextColor(colorWhite);
    winMsg -> setPos(200, 500);

    enemyMsg -> setFont(fontSmall);
    enemyMsg -> setDefaultTextColor(colorRed);
    enemyMsg -> setPos(10, 10);

    powerUpMsg -> setFont(fontBig);
    powerUpMsg -> setDefaultTextColor(colorWhite);
    powerUpMsg -> setPos(200, 500);

    setFixedSize(800, 800);

    scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, 800, 800);
    setScene(scene);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QFile file(":/textFile/gameTextFile.txt");
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        return;
    }

    QTextStream inputFile(&file);
    QString text = inputFile.readAll();
    QString slashN = "\n";
    QString text2 = "";
    file.close();

    for(int i = 0; i < text.size(); i++)
    {
        if(text[i] != slashN)
        {
            text2.append(text[i]);
        }
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            int x = text2[i * 10 + j].digitValue();
            arrayOfMapN[i][j] = x;
        }
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            switch (arrayOfMapN[i][j]) {
            case 0: { //empty land
                QGraphicsRectItem* item = new QGraphicsRectItem(j * 80, i * 80, 80, 80);
                QBrush greenBrush(Qt::green);
                item->setBrush(greenBrush);
                scene->addItem(item);
                break;
            }
            case 1: { //clan castle
                ClanCastle* c = new ClanCastle(j*80, i*80, this); // const
                scene->addItem(c);
                map.push_back(c);
                break;
            }
            case 2: { //defence unit
                Defence *d;
                switch (defenceType)
                {
                case 1: {
                    d = new Canon(j*80, i*80, this);
                    break;
                }
                case 2: {
                    d = new ArcherTower(j*80, i*80, this);
                    break;
                }
                case 3: {
                    d = new WizardTower(j*80, i*80, this);
                    break;
                }
                }
                scene->addItem(d);
                d->DisplayArrow();
                map.push_back(d);
                defence = d;
                break;
            }
            case 3: { //fence
                Fence* f = new Fence(j*80, i*80);
                scene->addItem(f);
                map.push_back(f);
                break;
            }
            default:
                break;
            }
        }
    }

    scene -> addItem(startMsg);

    QTimer::singleShot(2500, qApp, [this](){ freeze = false; });
}

void Game::generateEnemy(){
    Enemy* e;
    int randomX;
    int randomY;
    for(int i = 0; i < enemyCount; i ++)
    {
        randomX = rand()%900+50;
        randomY = rand()%200 + 600;
        e = new Enemy(randomX, randomY, this);
        enemies.push_back(e);
        scene->addItem(e);
    }
}

void Game::keyPressEvent(QKeyEvent* event)
{
    if(!freeze)
    {
        if(! started)
        {
            if(event->key()== Qt::Key_Space)
            {
                QTimer* winTimer = new QTimer();
                connect(winTimer, &QTimer::timeout, this, &Game::win);
                winTimer->start(winTime);
                started = true;
                scene->removeItem(startMsg);
                generateEnemy();
                QTimer* EnemyTimer = new QTimer();
                connect(EnemyTimer, &QTimer::timeout, this, &Game::generateEnemy);
                EnemyTimer->start(enemyTime);

                for(int i = 0; i < 5; i++)
                {
                    CitizenWorker* c = new CitizenWorker(260, 0+i*50, this);
                    citizenWorkers.push_back(c);
                    scene->addItem(c);
                }

                scene->addItem(enemyMsg);
            }
        }
        else
        {
            if(event->key()== Qt::Key_Left)
            {
                defence->aimLeft();
            }
            else if(event->key()== Qt::Key_Right)
            {
                defence->aimRight();
            }
            else if(event->key()== Qt::Key_Space)
            {
                defence->shoot();
            }

        }
    }
}

void Game::gameOver()
{
    scene->addItem(loseMsg);
    QTimer::singleShot(5000, qApp, &QApplication::quit);
}

void Game::win()
{
    if(level < 5)
    {
        nextLevel();
    }
    else
    {
        scene->addItem(winMsg);
        QTimer::singleShot(5000, qApp, &QApplication::quit);
    }
}

void Game::defeatEnemy(Enemy* e)
{
    score++;
    for(int i = 0; i < enemies.size(); i++)
    {
        if(enemies.at(i) == e)
        {
            enemies.erase(enemies.begin()+i);
        }
    }
    if(score != 0 && score%10 == 0)
    {
        scene->addItem(powerUpMsg);
        defence->increasePower(50);
        QTimer::singleShot(2000, qApp, [this](){ scene->removeItem(powerUpMsg); });
    }
    scene->removeItem(enemyMsg);
    enemyMsg->setPlainText(QString("Score: ") + QString::number(score));
    scene->addItem(enemyMsg);
}

void Game::nextLevel()
{
    int nextLevel = level + 1;
    delete this;
    game = new Game(nextLevel);
    game->show();
    game->setFocus();
}

Game::~Game()
{
    for(int i = 0; i < enemies.size(); i++)
    {
        delete enemies[i];
    }
    for(int i = 0; i < citizenWorkers.size(); i++)
    {
        delete citizenWorkers[i];
    }
    for(int i = 0; i < map.size(); i++)
    {
        delete map[i];
    }
    delete startMsg;
    delete loseMsg;
    delete winMsg;
    delete enemyMsg;
    delete powerUpMsg;
    delete scene;
}


