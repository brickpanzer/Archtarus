#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>
#include <QDebug>
#include <QRandomGenerator>

#include "planet.h"

Planet::Planet(int x, int y,int x_off, int y_off, int size) : x_(x), y_(y),x_offset_(x_off),y_offset_(y_off), size_(size)
{
    setAcceptHoverEvents(true);
//    x_offset_ = QRandomGenerator::global()->bounded(0,50);
//    y_offset_ = QRandomGenerator::global()->bounded(0,50);
    switch(size){
    case 0 : parts_ = 0;
             fuel_ = 0;
             people_ = 0;
             width_ = 0;
             color_.setRgb(255,255,255);
             break;
    case 1 : parts_ = QRandomGenerator::global()->bounded(0,10);
             fuel_ = QRandomGenerator::global()->bounded(50,300);
             people_ = QRandomGenerator::global()->bounded(0,5);
             width_ = 30;
             color_.setRgb(191,55,45);
             break;
    case 2 : parts_ = QRandomGenerator::global()->bounded(5,40);
             fuel_ = QRandomGenerator::global()->bounded(100,450);
             people_ = QRandomGenerator::global()->bounded(3,15);
             width_ = 50;
             color_.setRgb(221,105,51);
             break;
    case 3 : parts_ = QRandomGenerator::global()->bounded(20,120);
             fuel_ = QRandomGenerator::global()->bounded(230,600);
             people_ = QRandomGenerator::global()->bounded(10,30);
             width_ = 75;
             color_.setRgb(234,181,65);
             break;
    }
}

QRectF Planet::boundingRect() const
{
    return QRectF(x_, y_, width_, width_);
}

QPainterPath Planet::shape() const
{
    QPainterPath path;
    path.addEllipse(x_, y_, width_, width_);
    return path;
}


void Planet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QBrush b = painter->brush();
//    QColor black;
//    black.setRgb(0,0,0);

//    painter->setBrush(QBrush(black.dark(option->state & QStyle::State_Sunken ? 120 : 100)));

//    painter->drawRect(QRect(this->x_, this->y_, 100, 100));

    painter->setBrush(QBrush(color_.dark(option->state & QStyle::State_Sunken ? 120 : 100)));

    painter->drawEllipse(QRect(this->x_ + this->x_offset_, this->y_ + this->y_offset_, width_, width_));
    painter->setBrush(b);
}

void Planet::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    QGraphicsItem::hoverEnterEvent(event);
    qDebug() << "Class: " << size_;
    qDebug() << "Parts: " << parts_;
    qDebug() << "Fuel: " << fuel_;
    qDebug() << "Inhabidants: " << people_;
}

void Planet::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    QGraphicsItem::hoverLeaveEvent(event);
    qDebug() << "Exited";
}
