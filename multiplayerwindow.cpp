#include "multiplayerwindow.h"
#include "ui_multiplayerwindow.h"
#include "Game.h"

extern Game* game;

MultiplayerWindow::MultiplayerWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MultiplayerWindow)
{
    ui->setupUi(this);
}

MultiplayerWindow::~MultiplayerWindow()
{
    delete ui;
}

void MultiplayerWindow::on_pushButtonCanon_clicked()
{
    game = new Game(1);
    game->show();
    game->setFocus();
    this->hide();
}

void MultiplayerWindow::on_pushButtonArcherTower_clicked()
{
    game = new Game(2);
    game->show();
    game->setFocus();
    this->hide();
}

void MultiplayerWindow::on_pushButtonWizardTower_clicked()
{
    game = new Game(3);
    game->show();
    game->setFocus();
    this->hide();
}
