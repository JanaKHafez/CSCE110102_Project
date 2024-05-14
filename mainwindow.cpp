#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Game.h"

extern int mode;
extern Game* game;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonSinglePlayer_clicked()
{
    mode = 1;
    game = new Game();
    game->show();
    game->setFocus();
    this->hide();
}

void MainWindow::on_pushButtonMultiplayer_clicked()
{
    mode = 2;
    game = new Game();
    game->show();
    game->setFocus();
    this->hide();
}
