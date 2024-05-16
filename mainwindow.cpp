#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Game.h"
#include "multiplayerwindow.h"
#include "helpwindow.h"

extern int mode;
extern Game* game;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix = QPixmap(":/ui_Images/wallpaperflare.com_wallpaper (3).jpg");
    pix=pix.scaled(width(),height());
    ui->label->setPixmap(pix);
    QPixmap pix2 = QPixmap(":/ui_Images/multiwall.jpeg");
    QPixmap pix3 = QPixmap(":/ui_Images/Supermago.jpeg");
    //ui->singleLabel->setPixmap(pix3);


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
    MultiplayerWindow *multiplayerWindow = new MultiplayerWindow();
    multiplayerWindow->show();
    this->hide();
}

void MainWindow::on_pushButton_getHelp_clicked()
{
    helpWindow *helpWindow= new class helpWindow ();
    helpWindow ->show();
    this->hide();
}

