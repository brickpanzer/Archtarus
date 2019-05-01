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
    Ship * starting_ship = new Ship(100,view->frameSize().height() - 100,0);
    players_[0]->add_ship(starting_ship);
    scene->addItem(starting_ship);
    connect(starting_ship, &Ship::ShipClicked, this, &MainWindow::ShipClickedSlot);
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
    test.setText("Fleet Status: " + QString::number(players_[current_player_]->get_fleet_lvl()));

    test.exec();

    if(test.clickedButton() == upgrade_fleet) {
        if(players_[current_player_]->level_fleet()){
            //add new ship
            int x_coord;
            int y_coord;
            switch(current_player_){
                case 0 : x_coord = 100;
                         y_coord = ui->graphicsView->frameSize().height() - 100;
                         break;
                case 1 : x_coord = ui->graphicsView->frameSize().width() - 100;
                         y_coord = 100;
                         break;
                case 2 : x_coord = ui->graphicsView->frameSize().width() - 100;
                         y_coord = ui->graphicsView->frameSize().height() - 100;
                         break;
                case 3 : x_coord = 100;
                         y_coord = 100;
                         break;
                default : x_coord = 0;
                          y_coord = 0;
                          break;
            }
            Ship * tmp = new Ship(x_coord,y_coord,current_player_);
            connect(tmp, &Ship::ShipClicked, this, &MainWindow::ShipClickedSlot);
            scene->addItem(tmp);
            players_[current_player_]->add_ship(tmp);
        }
        else{
            //another modal?
        }
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
    //move previous players ships based on nav data
    if(nav_ships_.size() > 0 && nav_planets_.size() > 0){
        for(int i = 0; i < nav_ships_.size(); i++){
           nav_ships_.at(i)->move(nav_planets_.at(i)->get_x(), nav_planets_.at(i)->get_y());
        }
    }
    //add planets + remove fuel

    //clear nav data
    nav_ships_.clear();
    nav_planets_.clear();

    //check win condition
    qDebug() << "My Planets: " << players_[current_player_]->get_planets_();
    qDebug() << "Needed Planets: " << total_planets_;
    if(players_[current_player_]->get_planets_() == total_planets_){
        qDebug() << "Win Condition!";
        QMessageBox you_win;
        you_win.setText("Player: " + QString::number(current_player_ + 1) + " wins!");
        you_win.exec();
    }
    //change player
    current_player_ = (current_player_ + 1) % total_players_;
    ui->menuCurrent_Player->setTitle("Current player:" + QString::number(current_player_ + 1));
    //update stats
    players_[current_player_]->call_turn();

    //set fuel guage
    QString fuel_str = "Fuel: ";
    fuel_str.append(QString::number(players_[current_player_]->get_fuel()));
    ui->menuFuel_0->setTitle(fuel_str);

    //set win percentage
    QString win_str = "Win %: ";
    double win = players_[current_player_]->get_planets_() / total_planets_;
    //QString::number(players_[current_player_]->get_planets_()) + "/" + QString::number(total_planets_)
    win_str.append(QString::number(players_[current_player_]->get_planets_()) + "/" + QString::number(total_planets_)); //current players planet count / all planets in game
    ui->menuWin_0->setTitle(win_str);
}

void MainWindow::on_actionAdd_Player_triggered()
{
    Ship * tmp2;
    Ship * tmp3;
    Ship * tmp4;
    switch(total_players_){
        case 1 : players_[1] = new Player(ui->graphicsView->frameSize().width(),0,2);
                 tmp2 = new Ship(ui->graphicsView->frameSize().width() - 100,100,1);
                 players_[1]->add_ship(tmp2);
                 scene->addItem(tmp2);
                 connect(tmp2, &Ship::ShipClicked, this, &MainWindow::ShipClickedSlot);
                 total_players_++;
                 break;
        case 2 : players_[2] = new Player(ui->graphicsView->frameSize().width(),ui->graphicsView->frameSize().height(),3);
                 tmp3 = new Ship(ui->graphicsView->frameSize().width() - 100,ui->graphicsView->frameSize().height() - 100,2);
                 players_[2]->add_ship(tmp3);
                 scene->addItem(tmp3);
                 connect(tmp3, &Ship::ShipClicked, this, &MainWindow::ShipClickedSlot);
                 total_players_++;
                 break;
        case 3 : players_[3] = new Player(0,0,4);
                 tmp4 = new Ship(100,100,3);
                 players_[3]->add_ship(tmp4);
                 scene->addItem(tmp4);
                 connect(tmp4, &Ship::ShipClicked, this, &MainWindow::ShipClickedSlot);
                 total_players_++;
                 break;
        default:
                 break;
    }
}

void MainWindow::PlanetClickedSlot(Planet * p)
{
    if(nav_ships_.size() == nav_planets_.size() && nav_ships_.size() > 0){
        nav_planets_.back() = p;
    }
    else if(nav_ships_.size() != nav_planets_.size() && nav_ships_.size() > 0){
        nav_planets_.push_back(p);
    }
    int dist;
    //if planet already owned
    if(p->get_owner_id() != -1){

        //fight for planet
        //if attacker fleet level is greater than defenders, attackers win planet. otherwise tie or loss, defenders keep the planet
        if(players_[current_player_]->get_fleet_lvl() > players_[p->get_owner_id()]->get_fleet_lvl()){
            //delete planet from previous owner
            players_[p->get_owner_id()]->remove_planet(p);

            players_[current_player_]->add_planet(p);
            p->ChangePlanetOwner(players_[current_player_]->get_player_color(), current_player_);
            qDebug() << "Planet invaded";
        }
        else{
            qDebug() << "Planet invasion failed";
        }

    }
    else{
        players_[current_player_]->add_planet(p);
        p->ChangePlanetOwner(players_[current_player_]->get_player_color(), current_player_);
        qDebug() << "Empty planet taken";
    }
}

void MainWindow::ShipClickedSlot(Ship * s){
    if(nav_ships_.size() == 0){
        nav_ships_.push_back(s);
    }
    else if(nav_ships_.size() > 0 && nav_ships_.size() == nav_planets_.size() + 1){
        nav_ships_.back() = s;
    }
    else if(nav_ships_.size() > 0 && nav_ships_.size() == nav_planets_.size()){
        nav_ships_.push_back(s);
    }
}
