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
#include "mainwindow.h"

extern Game* game;
extern int mode;

Game::Game(int thisLevel, QWidget* parent) : QGraphicsView(parent) {

    powerUp = nullptr;
    score = 0;
    score2 = 0;
    ClanCastle::castleCount = 0;
    ClanCastle::castleCount2 = 0;

    level = thisLevel;

    switch (level)
    {
    case 1: {
        goal = 1.5; //time in minutes
        enemyTime = 13000;
        enemyCount = 2;
        defenceType = 1;
        enemySpeed = 50; //time between movement (increase to decrease speed)
        mapFile.setFileName(":/textFile/gameTextFile.txt");
        break;
    }
    case 2: {
        goal = 1.5;
        enemyTime = 20000;
        enemyCount = 3;
        defenceType = 2;
        enemySpeed = 100;
        mapFile.setFileName(":/textFile/gameTextFile3.txt");
        break;
    }
    case 3: {
        goal = 1.5;
        enemyTime = 20000;
        enemyCount = 4;
        defenceType = 3;
        enemySpeed = 50;
        mapFile.setFileName(":/textFile/gameTextFile3.txt");
        break;
    }
    case 4: {
        goal = 2;
        enemyTime = 12500;
        enemyCount = 3;
        defenceType = 2;
        enemySpeed = 100;
        mapFile.setFileName(":/textFile/gameTextFile2.txt");
        break;
    }
    case 5: {
        goal = 2;
        enemyTime = 17500;
        enemyCount = 5;
        defenceType = 3;
        enemySpeed = 50;
        mapFile.setFileName(":/textFile/gameTextFile2.txt");
        break;
    }
    }

    if(mode == 2)
    {
        goal = 0;
        enemyTime = 17500;
        enemyCount = 2;
        defenceType = 1;
        enemySpeed = 50;
        mapFile.setFileName(":/textFile/MultiplayerMap.txt");
    }

    winMsg = new QGraphicsTextItem(QString("You Win!!!"));
    loseMsg = new QGraphicsTextItem(QString("You Lose!"));
    scoreMsg = new QGraphicsTextItem(QString("Score: ") + QString::number(score));
    score2Msg = new QGraphicsTextItem(QString("Score: ") + QString::number(score2));
    powerUpMsg = new QGraphicsTextItem(QString("Power Up!"));
    countdownMsg = new QGraphicsTextItem(QString(""));
    if(mode == 1)
    {
        if(level == 1) {startMsg = new QGraphicsTextItem(QString("Level ") + QString::number(level) + "\n" + QString("Survive for ") + QString::number(goal*60) + QString(" seconds") + "\n" + QString("Press space to start"));}
        else {startMsg = new QGraphicsTextItem(QString("Level ") + QString::number(level -1) + QString(" Completed!"));}
    }
    else if(mode == 2)
    {
        startMsg = new QGraphicsTextItem(QString("Press space to start"));
    }

    QFont fontBig;
    QFont fontSmall;
    QColor colorWhite(Qt::white);
    QColor colorRed(Qt::red);
    fontBig.setPointSize(50);
    fontSmall.setPointSize(16);

    startMsg -> setFont(fontBig);
    startMsg -> setDefaultTextColor(colorWhite);
    if(mode == 1) {startMsg -> setPos(0, 450);}
    else if(mode == 2) {startMsg -> setPos(0, 330);}

    loseMsg -> setFont(fontBig);
    loseMsg -> setDefaultTextColor(colorRed);
    loseMsg -> setPos(250, 230);

    winMsg -> setFont(fontBig);
    winMsg -> setDefaultTextColor(colorWhite);
    winMsg -> setPos(250, 230);

    scoreMsg -> setFont(fontSmall);
    scoreMsg -> setDefaultTextColor(colorRed);
    scoreMsg -> setPos(10, 30);

    score2Msg -> setFont(fontSmall);
    score2Msg -> setDefaultTextColor(colorRed);
    score2Msg -> setPos(10, 700);

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
                ClanCastle* c;
                if(mode == 1) {c = new ClanCastle(j*80, i*80, this);}
                if(mode == 2)
                {
                    if(i <= 4)
                    {
                        c = new ClanCastle(j*80, i*80, this, 1);
                    }
                    else
                    {
                        c = new ClanCastle(j*80, i*80, this, 2);
                    }
                }
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

                if(mode == 1 || i <= 4)
                {
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
                }

                else if(mode == 2 && i > 4)
                {
                    Defence *d;
                    switch (defenceType)
                    {
                    case 1: {
                        d = new Canon(j*80, i*80, this, 2);
                        break;
                    }
                    case 2: {
                        d = new ArcherTower(j*80, i*80, this, 2);
                        break;
                    }
                    case 3: {
                        d = new WizardTower(j*80, i*80, this, 2);
                        break;
                    }
                    }
                    scene->addItem(d);
                    d->DisplayPic();
                    d->DisplayArrow();
                    map.push_back(d);
                    defence2 = d;
                }

                break;
            }
            case 3: { //fence
                Fence* f;
                if(mode == 1 || i <= 4) {f = new Fence(j*80, i*80);}
                else if(mode == 2 && i > 4) {f = new Fence(j*80, i*80, 2);}
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
    audioPicON->setPos(725, 60);

    audioPicOFF = new QGraphicsPixmapItem();
    QPixmap audioPixOFF = QPixmap(":/images/audioOFF.png");
    QPixmap scaledPixmapAudioOFF = audioPixOFF.scaled(70, 80);
    audioPicOFF->setPixmap(scaledPixmapAudioOFF);
    audioPicOFF->setPos(725, 60);

    pausePic = new QGraphicsPixmapItem();
    QPixmap pausePix = QPixmap(":/images/pauseIcon.png");
    QPixmap scaledPixmapPause = pausePix.scaled(320, 200);
    pausePic->setPixmap(scaledPixmapPause);
    pausePic->setPos(540, -65);

    playPic = new QGraphicsPixmapItem();
    QPixmap playPix = QPixmap(":/images/playIcon.png");
    QPixmap scaledPixmapPlay = playPix.scaled(440, 360);
    playPic->setPixmap(scaledPixmapPlay);
    playPic->setPos(490, -140);

    scene->addItem(audioPicON);
    scene->addItem(pausePic);

    QGraphicsPixmapItem *restartPic = new QGraphicsPixmapItem();
    QPixmap restartPix = QPixmap(":/images/restartButton.png");
    QPixmap scaledPixmapRestart = restartPix.scaled(40, 40);
    restartPic->setPixmap(scaledPixmapRestart);
    restartPic->setPos(740, 20);
    scene->addItem(restartPic);

    if(level > 1) {QTimer::singleShot(5000, qApp, [this](){
            freeze = false;
            scene -> removeItem(startMsg);
            startMsg -> setPlainText(QString("Level ") + QString::number(level) + "\n" + QString("Survive for ") + QString::number(goal*60) + QString(" seconds") + "\n" + QString("Press space to start"));
            scene -> addItem(startMsg);
        });}
    else {freeze = false;}
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

                gameTimer = new QTimer();
                connect(gameTimer, &QTimer::timeout, this, &Game::millisecond);
                gameTimer->start(100);

                if(mode == 1)
                {
                    for(int i = 0; i < 5; i++)
                    {
                        CitizenWorker* c = new CitizenWorker(260, 0+i*50, this);
                        citizenWorkers.push_back(c);
                        scene->addItem(c);
                    }
                }
                else if(mode == 2)
                {
                    for(int i = 0; i < 3; i++)
                    {
                        CitizenWorker* c = new CitizenWorker(260 + i * 50, 50, this, 1);
                        citizenWorkers.push_back(c);
                        scene->addItem(c);
                    }
                    for(int i = 0; i < 3; i++)
                    {
                        CitizenWorker* c = new CitizenWorker(340 + i * 50, 700, this, 2);
                        citizenWorkers.push_back(c);
                        scene->addItem(c);
                    }
                }

                scene->addItem(scoreMsg);
                if(mode == 2)
                {
                    scene->addItem(score2Msg);
                }
                scene->addItem(countdownMsg);

                generateEnemy();
            }
        }
        else if(!paused)
        {
            if(mode == 1)
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

            if(mode == 2)
            {
                if(event->key()== Qt::Key_Left)
                {
                    defence->aimLeft();
                }
                if(event->key()== Qt::Key_Right)
                {
                    defence->aimRight();
                }
                if(event->key()== Qt::Key_Up)
                {
                    defence->shoot();
                }
                if(event->key() == Qt::Key_A)
                {
                    defence2->aimLeft();
                }
                if(event->key() == Qt::Key_D)
                {
                    defence2->aimRight();
                }
                if(event->key() == Qt::Key_W)
                {
                    defence2->shoot();
                }
            }
        }
    }
}

void Game::mousePressEvent(QMouseEvent* event)
{
    QPointF mousePoint = event->pos();
    qreal x = mousePoint.x();
    qreal y = mousePoint.y();

    if(x >= 735 && x <= 780 && y >= 75 && y <= 120)
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

    else if(started && x >= 690 && x <= 710 && y >= 20 && y <= 55)
    {
        if(paused == false)
        {
            scene->removeItem(pausePic);
            scene->addItem(playPic);
            pause();
            paused = true;
        }
        else
        {
            scene->removeItem(playPic);
            scene->addItem(pausePic);
            play();
            paused = false;
        }
    }

    if(over)
    {
        if(x >= 50 && x <= 370 && y >= 360 && y <= 680)
        {
            delete this;
            MainWindow *mainWindow = new MainWindow();
            mainWindow->show();
        }
        if(x >= 450 && x <= 770 && y >= 360 && y <= 680)
        {
            restart();
        }
    }
}

void Game::millisecond()
{
    time+=100;

    if(mode == 1)
    {
        if(time%1000 == 0)
        {
            int min;
            int sec;
            int thisTime;

            thisTime = goal*60 - time/1000;
            sec = thisTime%60;
            min = (thisTime - sec)/60;

            scene->removeItem(countdownMsg);
            if(sec > 9) {countdownMsg->setPlainText(QString::number(min) + QString(":") + QString::number(sec));}
            else {countdownMsg->setPlainText(QString::number(min) + QString(":0") + QString::number(sec));}
            scene->addItem(countdownMsg);
        }

        if(goal*60 <= time/1000)
        {
            win();
        }

        else if(time % enemyTime == 0)
        {
            generateEnemy();
        }

        else if(time % 30000 == 0)
        {
            generatePowerUp();
        }
    }

    else if(mode == 2)
    {
        if(time % enemyTime == 0)
        {
            generateEnemy();
        }
    }
}

void Game::end()
{
    over = true;
    pause();

    QGraphicsPixmapItem* exitPic = new QGraphicsPixmapItem();
    QPixmap exitPix = QPixmap(":/images/exit.jpg");
    QPixmap scaledPixmapExit = exitPix.scaled(320, 320);
    exitPic->setPixmap(scaledPixmapExit);
    exitPic->setPos(50, 360);
    scene->addItem(exitPic);

    QGraphicsPixmapItem *restartPic = new QGraphicsPixmapItem();
    QPixmap restartPix = QPixmap(":/images/restartButton.png");
    QPixmap scaledPixmapRestart = restartPix.scaled(320, 320);
    restartPic->setPixmap(scaledPixmapRestart);
    restartPic->setPos(450, 360);
    scene->addItem(restartPic);
}

void Game::restart()
{
    delete this;
    game = new Game(1);
    game->show();
    game->setFocus();
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
    int thisEnemyX;
    int thisEnemyY;
    for(int i = 0; i < enemyCount; i ++)
    {
        if(mode == 1)
        {
            thisEnemyX = rand()%800;
            thisEnemyY = 800;
        }
        if(mode == 2)
        {
            thisEnemyX = rand()%800;
            thisEnemyY = 320 + rand()%81;
        }
        e = new Enemy(thisEnemyX, thisEnemyY, enemySpeed, this);
        enemies.push_back(e);
        scene->addItem(e);
    }
}

void Game::gameOver(int p)
{
    if(mode == 1)
    {    if(audio)
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

        scene->addItem(loseMsg);
        QGraphicsPixmapItem* gameOverPic = new QGraphicsPixmapItem();
        QPixmap gameOverPix = QPixmap(":/images/GameOverImage.jpg");
        QPixmap scaledPixmapGameOver = gameOverPix.scaled(320, 320);
        gameOverPic->setPixmap(scaledPixmapGameOver);
        gameOverPic->setPos(240, 360);
        //scene->addItem(gameOverPic);
    }

    else if(mode == 2)
    {
        if(audio)
        {
            QMediaPlayer *victoryMedia;
            QAudioOutput *victoryAudio;
            victoryAudio= new QAudioOutput();
            victoryAudio -> setVolume (100);
            victoryMedia = new QMediaPlayer ();
            victoryMedia->setAudioOutput(victoryAudio);
            victoryMedia ->setSource(QUrl("qrc:/new/prefix1/Victory.mp3"));
            victoryMedia ->play();
        }

        if(p == 2) {p = 1;}
        else {p = 2;}

        winMsg->setPlainText(QString("Player ") + QString::number(p) + QString(" wins!"));
        scene->addItem(winMsg);
    }

    end();
}

void Game::win()
{
    scene->addItem(winMsg);

    if(audio)
    {
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
        end();
    }
}

void Game::defeatEnemy(Enemy* e, int p)
{
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

    if(p == 1)
    {
        score++;

        scene->removeItem(scoreMsg);
        scoreMsg->setPlainText(QString("Score: ") + QString::number(score));
        scene->addItem(scoreMsg);

        if(score != 0 && score%10 == 0 && mode == 1)
        {
            scene->addItem(powerUpMsg);
            defence->increasePower(50);
            QTimer::singleShot(2000, qApp, [this](){ scene->removeItem(powerUpMsg); });
        }
    }

    if(p == 2)
    {
        score2++;

        scene->removeItem(score2Msg);
        score2Msg->setPlainText(QString("Score: ") + QString::number(score2));
        scene->addItem(score2Msg);
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

void Game::hitPowerUp()
{
    scene -> removeItem(powerUp);
    delete powerUp;
    powerUp = nullptr;
    scene->addItem(powerUpMsg);
    defence->increasePower(50);
    QTimer::singleShot(2000, qApp, [this](){ scene->removeItem(powerUpMsg); });
}

void Game::pause()
{
    if(!paused)
    {
        if(gameTimer != nullptr) {delete gameTimer;}
        gameTimer = nullptr;

        for(int i = 0; i < enemies.size(); i++)
        {
            enemies[i]->pause();
        }

        for(int i = 0; i < citizenWorkers.size(); i++)
        {
            citizenWorkers[i]->pause();
        }
        paused = true;
    }
}

void Game::play()
{
    if(paused)
    {
        gameTimer = new QTimer();
        connect(gameTimer, &QTimer::timeout, this, &Game::millisecond);
        gameTimer->start(100);

        for(int i = 0; i < enemies.size(); i++)
        {
            enemies[i]->play();
        }

        for(int i = 0; i < citizenWorkers.size(); i++)
        {
            citizenWorkers[i]->play();
        }
        paused = false;
    }
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
    delete scoreMsg;
    delete score2Msg;
    delete powerUpMsg;
    delete scene;
}


