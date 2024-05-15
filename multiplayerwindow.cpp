#include "multiplayerwindow.h"
#include "ui_multiplayerwindow.h"
#include "Game.h"

extern Game* game;

MultiplayerWindow::MultiplayerWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MultiplayerWindow)
{
    ui->setupUi(this);


    resize(900, 900);


    QPixmap wallpaper = QPixmap(":/ui_Images/background3.jpg").scaled(900, 900);
    ui->label->setPixmap(wallpaper);
    ui->label->resize(900, 900);


    int horizontalMargin = (width() - (3 * 300)) / 2;


    ui->labelCanonPic->resize(300, 300);
    ui->labelCanonPic->move(horizontalMargin, (height() - 300) / 2);
    QPixmap pix = QPixmap(":/images/TOWER1.png").scaled(300, 300);
    ui->labelCanonPic->setPixmap(pix);

    ui->labelArcherTowerPic->resize(300, 300);
    ui->labelArcherTowerPic->move(horizontalMargin + 300, (height() - 300) / 2);
    QPixmap pix2 = QPixmap(":/images/TOWER3.png").scaled(300, 300);
    ui->labelArcherTowerPic->setPixmap(pix2);

    ui->labelWizardTowerPic->resize(300, 300);
    ui->labelWizardTowerPic->move(horizontalMargin + 600, (height() - 300) / 2);
    QPixmap pix3 = QPixmap(":/images/TOWER2.png").scaled(300, 300);
    ui->labelWizardTowerPic->setPixmap(pix3);


    int buttonWidth = 250;
    int buttonHeight = 50;
    int buttonX = (width() - (3 * buttonWidth)) / 2;
    int buttonY = height() - buttonHeight - 200;


    ui->pushButtonCanon->setGeometry(buttonX-50, buttonY, buttonWidth, buttonHeight);
    ui->pushButtonArcherTower->setGeometry(buttonX + buttonWidth + 10, buttonY, buttonWidth, buttonHeight);
    ui->pushButtonWizardTower->setGeometry(buttonX + 2 * (buttonWidth + 10) + 50, buttonY, buttonWidth, buttonHeight);
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
