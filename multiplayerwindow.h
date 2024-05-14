#ifndef MULTIPLAYERWINDOW_H
#define MULTIPLAYERWINDOW_H

#include <QDialog>

namespace Ui {
class MultiplayerWindow;
}

class MultiplayerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MultiplayerWindow(QWidget *parent = nullptr);
    ~MultiplayerWindow();

private:
    Ui::MultiplayerWindow *ui;

private slots:
    void on_pushButtonCanon_clicked();
    void on_pushButtonArcherTower_clicked();
    void on_pushButtonWizardTower_clicked();
};

#endif // MULTIPLAYERWINDOW_H
