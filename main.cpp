 #include <QApplication>
#include <QKeyEvent>
#include <QGraphicsTextItem>
#include "Game.h"
#include "ClanCastle.h"
#include "mainwindow.h"

Game *game;

bool audio = true;
int ClanCastle::castleCount = 0;
int ClanCastle::castleCount2 = 0;

int mode = 2;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*game = new Game();
    game->setFocus();
    //level 4 seg fault
    game->show();*/
    MainWindow w;
    w.show();
    return a.exec();
}
