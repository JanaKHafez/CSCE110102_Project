 #include <QApplication>
#include <QKeyEvent>
#include <QGraphicsTextItem>
#include "Game.h"
#include "ClanCastle.h"

Game *game;
bool audio = true;

int ClanCastle::castleCount = 0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game = new Game(1);
    game->show();
    game->setFocus();
    return a.exec();
}
