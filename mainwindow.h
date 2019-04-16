#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>

#include "planet.h"
#include "ship.h"
#include "player.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_Game_triggered();

    void on_actionPlayer_1_triggered();

private:
    Ui::MainWindow *ui;

    QGraphicsScene *scene;

    Planet * starmap_[179][191];

    Player * players_[4];
};

#endif // MAINWINDOW_H
