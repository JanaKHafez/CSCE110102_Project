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
#include <QMediaPlayer>
#include <QAudioOutput>
#include "Enemy.h"
#include "ClanCastle.h"
#include "Canon.h"
#include "ArcherTower.h"
#include "WizardTower.h"
#include "Fence.h"
#include "CitizenWorker.h"
#include "PowerUp.h"

extern Game* game;

Game::Game(int thisLevel, QWidget* parent) : QGraphicsView(parent) {

    powerUp = nullptr;
    score = 0;
    timePassed = 0;
    ClanCastle::castleCount = 0;

    level = thisLevel;

    switch (level)
    {
    case 1: {
        goal = 1.5; //time in minutes
        enemyTime = 15000;
        enemyCount = 2;
        defenceType = 1;
        enemySpeed = 10; //time between movement (increase to decrease speed)
        mapFile.setFileName(":/textFile/gameTextFile.txt");
        break;
    }
    case 2: {
        goal = 1.5;
        enemyTime = 20000;
        enemyCount = 3;
        defenceType = 2;
        enemySpeed = 20;
        mapFile.setFileName(":/textFile/gameTextFile3.txt");
        break;
    }
    case 3: {
        goal = 1.5;
        enemyTime = 20000;
        enemyCount = 4;
        defenceType = 3;
        enemySpeed = 10;
        mapFile.setFileName(":/textFile/gameTextFile3.txt");
        break;
    }
    case 4: {
        goal = 1;
        enemyTime = 15000;
        enemyCount = 3;
        defenceType = 2;
        enemySpeed = 10;
        mapFile.setFileName(":/textFile/gameTextFile2.txt");
        break;
    }
    case 5: {
        goal = 1;
        enemyTime = 20000;
        enemyCount = 5;
        defenceType = 3;
        enemySpeed = 10;
        mapFile.setFileName(":/textFile/gameTextFile2.txt");
        break;
    }
    }

    winMsg = new QGraphicsTextItem(QString("You Win!!!"));
    loseMsg = new QGraphicsTextItem(QString("You Lose!"));
    enemyMsg = new QGraphicsTextItem(QString("Score: ") + QString::number(score));
    powerUpMsg = new QGraphicsTextItem(QString("Power Up!"));
    countdownMsg = new QGraphicsTextItem(QString(""));
    if(level == 1) {startMsg = new QGraphicsTextItem(QString("Level ") + QString::number(level) + "\n" + QString("Survive for ") + QString::number(goal*60) + QString(" seconds") + "\n" + QString("Press space to start"));}
    else {startMsg = new QGraphicsTextItem(QString("Level ") + QString::number(level -1) + QString(" Completed!"));}

    QFont fontBig;
    QFont fontSmall;
    QColor colorWhite(Qt::white);
    QColor colorRed(Qt::red);
    fontBig.setPointSize(50);
    fontSmall.setPointSize(16);

    startMsg -> setFont(fontBig);
    startMsg -> setDefaultTextColor(colorWhite);
    startMsg -> setPos(0, 450);

    loseMsg -> setFont(fontBig);
    loseMsg -> setDefaultTextColor(colorRed);
    loseMsg -> setPos(200, 600);

    winMsg -> setFont(fontBig);
    winMsg -> setDefaultTextColor(colorWhite);
    winMsg -> setPos(0, 600);

    enemyMsg -> setFont(fontSmall);
    enemyMsg -> setDefaultTextColor(colorRed);
    enemyMsg -> setPos(10, 30);

    countdownMsg -> setFont(fontSmall);
    countdownMsg -> setDefaultTextColor(colorWhite);
    countdownMsg -> setPos(10, 0);

    powerUpMsg -> setFont(fontBig);
    powerUpMsg -> setDefaultTextColor(colorWhite);
    powerUpMsg -> setPos(200, 500);

    setFixedSize(800, 800);

    scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, 800, 800);
    setScene(scene);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    if (!mapFile.open(QFile::ReadOnly | QFile::Text)) {
        return;
    }

    QTextStream inputFile(&mapFile);
    QString text = inputFile.readAll();
    QString slashN = "\n";
    QString text2 = "";
    mapFile.close();

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

               // QGraphicsRectItem* item = new QGraphicsRectItem(j * 80, i * 80, 80, 80);
               //QBrush greenBrush(Qt::green);
               //item->setBrush(greenBrush);
               //item->setVisible(true);

               QGraphicsPixmapItem *item = new QGraphicsPixmapItem();
               QPixmap pix = QPixmap(":/images/greenland.jpeg");
               QPixmap scaledPixmap = pix.scaled(80, 80);
               item->setPixmap(scaledPixmap);
               item->setPos(j * 80, i * 80);
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

                QGraphicsPixmapItem *item = new QGraphicsPixmapItem();
                QPixmap pix = QPixmap(":/images/greenland.jpeg");
                QPixmap scaledPixmap = pix.scaled(80, 80);
                item->setPixmap(scaledPixmap);
                item->setPos(j * 80, i * 80);
                scene->addItem(item);

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
                d->DisplayPic();
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

    audioPicON = new QGraphicsPixmapItem();
    QPixmap audioPixON = QPixmap(":/images/audioOn.png");
    QPixmap scaledPixmapAudioON = audioPixON.scaled(60, 80);
    audioPicON->setPixmap(scaledPixmapAudioON);
    audioPicON->setPos(660, 0);

    audioPicOFF = new QGraphicsPixmapItem();
    QPixmap audioPixOFF = QPixmap(":/images/audioOFF.png");
    QPixmap scaledPixmapAudioOFF = audioPixOFF.scaled(70, 80);
    audioPicOFF->setPixmap(scaledPixmapAudioOFF);
    audioPicOFF->setPos(660, 0);

    scene->addItem(audioPicON);

    QGraphicsPixmapItem *restartPic = new QGraphicsPixmapItem();
    QPixmap restartPix = QPixmap(":/images/restartButton.png");
    QPixmap scaledPixmapRestart = restartPix.scaled(40, 40);
    restartPic->setPixmap(scaledPixmapRestart);
    restartPic->setPos(740, 20);
    scene->addItem(restartPic);

    if(level > 1) {QTimer::singleShot(2500, qApp, [this](){
            freeze = false;
            scene -> removeItem(startMsg);
            startMsg -> setPlainText(QString("Level ") + QString::number(level) + "\n" + QString("Survive for ") + QString::number(goal*60) + QString(" seconds") + "\n" + QString("Press space to start"));
            scene -> addItem(startMsg);
        });}
    else {freeze = false;}
}

void Game::mousePressEvent(QMouseEvent* event)
{
    QPointF mousePoint = event->pos();
    qreal x = mousePoint.x();
    qreal y = mousePoint.y();

    if(x >= 670 && x <= 715 && y >= 15 && y <= 60)
    {
        if(audio == true)
        {
            audio = false;
            scene->removeItem(audioPicON);
            scene->addItem(audioPicOFF);
        }
        else
        {
            audio = true;
            scene->removeItem(audioPicOFF);
            scene->addItem(audioPicON);
        }
    }

    else if(x >= 740 && x <= 780 && y <= 55 && y >= 20)
    {
        restart();
    }
}

void Game::restart()
{
    delete this;
    game = new Game(1);
    game->show();
    game->setFocus();
}

void Game::keyPressEvent(QKeyEvent* event)
{
    if(!freeze)
    {
        if(! started)
        {
            if(event->key()== Qt::Key_Space)
            {
                started = true;
                scene->removeItem(startMsg);

                generateEnemy();
                QTimer* EnemyTimer = new QTimer();
                connect(EnemyTimer, &QTimer::timeout, this, &Game::generateEnemy);
                EnemyTimer->start(enemyTime);

                countdownTimer = new QTimer();
                connect(countdownTimer, &QTimer::timeout, this, &Game::countdown);
                countdownTimer->start(1000);

                QTimer* powerUpTimer = new QTimer();
                connect(powerUpTimer, &QTimer::timeout, this, &Game::generatePowerUp);
                powerUpTimer->start(30000);

                for(int i = 0; i < 5; i++)
                {
                    CitizenWorker* c = new CitizenWorker(260, 0+i*50, this);
                    citizenWorkers.push_back(c);
                    scene->addItem(c);
                }

                scene->addItem(enemyMsg);
                scene->addItem(countdownMsg);
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

void Game::generatePowerUp()
{
    PowerUp * p;
    int randX;
    int randY;
    randX = rand()%700+50;
    randY = rand()%100 + 500;
    p = new PowerUp (this, randX, randY);
    powerUp = p;
    scene->addItem(p);
}

void Game::generateEnemy(){

    if(audio)
    {
        QMediaPlayer *enemyMedia;
        QAudioOutput *enemyAudio;
        enemyAudio= new QAudioOutput();
        enemyAudio -> setVolume (100);
        enemyMedia = new QMediaPlayer ();
        enemyMedia->setAudioOutput(enemyAudio);
        enemyMedia ->setSource(QUrl("qrc:/new/prefix1/incoming enemy.mp3"));
        enemyMedia ->play();
    }

    Enemy* e;
    int randomX;
    int randomY;
    for(int i = 0; i < enemyCount; i ++)
    {
        randomX = rand()%900+50;
        randomY = rand()%200 + 600;
        e = new Enemy(randomX, randomY, enemySpeed, this);
        enemies.push_back(e);
        scene->addItem(e);
    }
}

void Game::gameOver()
{
    scene->addItem(loseMsg);
    delete countdownTimer;
    QTimer::singleShot(5000, qApp, &QApplication::quit);

    if(audio)
    {
        QMediaPlayer *loseMedia;
        QAudioOutput *loseAudio;
        loseAudio= new QAudioOutput();
        loseAudio -> setVolume (50);
        loseMedia = new QMediaPlayer ();
        loseMedia->setAudioOutput(loseAudio);
        loseMedia ->setSource(QUrl("qrc:/new/prefix1/lose.mp3"));
        loseMedia ->play();
    }
}

void Game::win()
{
    scene->addItem(winMsg);

    if(audio)
    {
        scene->addItem(winMsg);
        QMediaPlayer *victoryMedia;
        QAudioOutput *victoryAudio;
        victoryAudio= new QAudioOutput();
        victoryAudio -> setVolume (100);
        victoryMedia = new QMediaPlayer ();
        victoryMedia->setAudioOutput(victoryAudio);
        victoryMedia ->setSource(QUrl("qrc:/new/prefix1/Victory.mp3"));
        victoryMedia ->play();
    }

    if(level < 5)
    {
        nextLevel();
    }
    else
    {
        QTimer::singleShot(5000, qApp, &QApplication::quit);
    }
}

void Game::defeatEnemy(Enemy* e)
{
    score++;

    if(audio)
    {
        QMediaPlayer *scoreMedia;
        QAudioOutput *scoreAudio;
        scoreAudio= new QAudioOutput();
        scoreAudio -> setVolume (50);
        scoreMedia = new QMediaPlayer ();
        scoreMedia->setAudioOutput(scoreAudio);
        scoreMedia ->setSource(QUrl("qrc:/new/prefix1/score.mp3"));
        scoreMedia ->play();
    }

    for(int i = 0; i < enemies.size(); i++)
    {
        if(enemies.at(i) == e)
        {
            enemies.erase(enemies.begin()+i);
        }
    }

    scene->removeItem(enemyMsg);
    enemyMsg->setPlainText(QString("Score: ") + QString::number(score));
    scene->addItem(enemyMsg);

    if(score != 0 && score%10 == 0)
    {
        scene->addItem(powerUpMsg);
        defence->increasePower(50);
        QTimer::singleShot(2000, qApp, [this](){ scene->removeItem(powerUpMsg); });
    }
}

void Game::nextLevel()
{
    int nextLevel = level + 1;

    if(audio)
    {
        QMediaPlayer *nextLevelMedia;
        QAudioOutput *nextLevelAudio;
        nextLevelAudio= new QAudioOutput();
        nextLevelAudio -> setVolume (100);
        nextLevelMedia = new QMediaPlayer ();
        nextLevelMedia->setAudioOutput(nextLevelAudio);
        nextLevelMedia ->setSource(QUrl("qrc:/new/prefix1/nextLevel.mp3"));
        nextLevelMedia ->play();
    }

    delete this;
    game = new Game(nextLevel);
    game->show();
    game->setFocus();
}

void Game::countdown()
{
    timePassed++;

    int min;
    int sec;
    int time;

    time = goal*60 - timePassed;
    sec = time%60;
    min = (time - sec)/60;

    scene->removeItem(countdownMsg);
    if(sec > 9) {countdownMsg->setPlainText(QString::number(min) + QString(":") + QString::number(sec));}
    else {countdownMsg->setPlainText(QString::number(min) + QString(":0") + QString::number(sec));}
    scene->addItem(countdownMsg);

    if(goal*60 <= timePassed)
    {
        delete countdownTimer;
        win();
    }
}

void Game::hitPowerUp()
{
    scene -> removeItem(powerUp);
    delete powerUp;
    powerUp = nullptr;
    scene->addItem(powerUpMsg);
    defence->increasePower(50);
    QTimer::singleShot(2000, qApp, [this](){ scene->removeItem(powerUpMsg); });
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


