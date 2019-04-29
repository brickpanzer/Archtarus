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

    void on_fleet_button_clicked();

    void on_take_turn_clicked();

    void on_actionAdd_Player_triggered();

    void PlanetClickedSlot(Planet * p);

signals:
    void change_player_id(QColor color);
private:
    Ui::MainWindow *ui;

    QGraphicsScene *scene;

    Planet * starmap_[10][18];

    Player * players_[4];

    int total_planets_;
    int total_players_;
    int current_player_;
};

#endif // MAINWINDOW_H
