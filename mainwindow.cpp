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

    for(int i = 0; i < 179; i++){
        for(int x = 0; x < 191; x++){
            const int x_coord = x * 100;
            const int y_coord = i * 100;
            int rand = QRandomGenerator::global()->bounded(0,16);
            int size;
            if(rand < 10){
                size = 0;
            }
            else if(rand == 10 || rand == 11 || rand == 12){
                size = 1;
            }
            else if(rand == 13 || rand == 14){
                size = 2;
            }
            else{
                size = 3;
            }
            Planet * temp = new Planet(x_coord,y_coord,size);
            starmap_[i][x] = temp;
            scene->addItem(temp);
        }
    }
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
    test.setText("This is where your stats will go!");
    test.exec();
}
