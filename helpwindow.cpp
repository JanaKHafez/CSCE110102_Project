#include "helpwindow.h"
#include "ui_helpwindow.h"
#include "mainwindow.h"

helpWindow::helpWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::helpWindow)
{
    ui->setupUi(this);
    resize(900,900);
}

helpWindow::~helpWindow()
{
    delete ui;
}

void helpWindow::on_pushButtonBackHelpWindow_clicked()
{
    MainWindow *main = new MainWindow();
    main->show();
    this->hide();
}

