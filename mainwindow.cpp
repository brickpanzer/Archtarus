#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QTimer>
#include <QRandomGenerator>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene;

    QGraphicsView * view = ui->graphicsView;

    view->setScene(scene);
    view->setSceneRect(0,0,view->frameSize().width(),view->frameSize().height());
    total_planets_ = 0;
    for(int i = 0; i < 10; i++){
        for(int x = 0; x < 18; x++){
            const int x_coord = (x * 100);
            const int y_coord = (i * 100);
            const int x_off = QRandomGenerator::global()->bounded(0,50);
            const int y_off = QRandomGenerator::global()->bounded(0,50);
            int rand = QRandomGenerator::global()->bounded(0,16);
            int size;
            if(rand < 10){
                size = 0;
            }
            else if(rand == 10 || rand == 11 || rand == 12){
                size = 1;
                total_planets_++;
            }
            else if(rand == 13 || rand == 14){
                size = 2;
                total_planets_++;
            }
            else{
                size = 3;
                total_planets_++;
            }
            Planet * temp = new Planet(x_coord,y_coord,x_off,y_off,size);
            starmap_[i][x] = temp;
            scene->addItem(temp);
            connect(temp, &Planet::PlanetClicked, this, &MainWindow::PlanetClickedSlot);
        }
    }

    //sets default player one to bottom left corner, as player number 1
    players_[0] = new Player(0,view->frameSize().height(),1);
    current_player_ = 0;
    total_players_ = 1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_Game_triggered()
{
    qDebug() << "clicked";
    QMessageBox test;
    test.setText("This is where your stats will go!");
    test.exec();
}

void MainWindow::on_actionPlayer_1_triggered()
{
    qDebug() << "clicked";
    QMessageBox test;
    test.setText("Stats for Player 1: \n"
                 "Fuel: " + QString::number(players_[0]->get_fuel()) + "\n"
                 "Parts: " + QString::number(players_[0]->get_parts()) + "\n"
                 "Crew: " + QString::number(players_[0]->get_people()) + "\n"
                 "Fleet Status: " + QString::number(players_[0]->get_fleet_lvl())
                 );
    test.exec();
}

void MainWindow::on_fleet_button_clicked()
{
    QMessageBox test;
    QPushButton * upgrade_fleet = test.addButton(tr("Upgrade?"), QMessageBox::ActionRole);
    QPushButton * fleet_cancel = test.addButton(QMessageBox::Abort);
    test.setDefaultButton(QMessageBox::Cancel);
    test.setText("Fleet Status: ");

    test.exec();

    if(test.clickedButton() == upgrade_fleet) {
        qDebug() << "Upgraded!";
        //upgrade
    }
    else if(test.clickedButton() == fleet_cancel) {
        qDebug() << "Exited window";
        //abort
    }
}

/*
 1 - confirms current players turn
 2 - loads new player
 3 - adds resources-per-tunr to current players pool
 4 - changes toolbar stats to match current player
*/
void MainWindow::on_take_turn_clicked()
{
    //change player
    current_player_ = (current_player_ + 1) % total_players_;

    //update stats

    players_[current_player_]->call_turn();

    //set fuel guage
    QString fuel_str = "Fuel: ";
    fuel_str.append(QString::number(players_[current_player_]->get_fuel()));
    ui->menuFuel_0->setTitle(fuel_str);

    //set win percentage
    QString win_str = "Win %: ";
    double win = players_[current_player_]->get_planets_() / total_planets_;
    win_str.append(QString::number(players_[current_player_]->get_planets_()) + "/" + QString::number(total_planets_)); //current players planet count / all planets in game
    ui->menuWin_0->setTitle(win_str);
}

void MainWindow::on_actionAdd_Player_triggered()
{
    switch(total_players_){
        case 1 : players_[1] = new Player(ui->graphicsView->frameSize().width(),0,2);
                 total_players_++;
                 break;
        case 2 : players_[2] = new Player(ui->graphicsView->frameSize().width(),ui->graphicsView->frameSize().height(),3);
                 total_players_++;
                 break;
        case 3 : players_[3] = new Player(0,0,4);
                 total_players_++;
                 break;
        default:
                 break;
    }
}

void MainWindow::PlanetClickedSlot(Planet * p)
{
    //if planet already owned
    if(p->get_owner_id() != -1){
        bool win = true;
        //fight for planet

        if(win){
            //delete planet from previous owner, decrement resources
            /*
             * for(Planet * x : player->get_planets()){
             *  if(x->id == p->id){
             *      player->get_planets().erase(x);
             *  }
             * }
            */
        }

    }
    players_[current_player_]->add_planet(p);
    p->ChangePlanetOwner(players_[current_player_]->get_player_color(), current_player_);
    qDebug() << "Planet clicked slot triggered";
}
