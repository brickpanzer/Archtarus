#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>
#include <QDebug>
#include <QRandomGenerator>

#include "ship.h"

Ship::Ship(const int x, const int y, const int player_id): x_(x), y_(y), player_id_(player_id)
{
    QColor color;
    switch(player_id_){
        case 1: color.setRgb(27,24,219);
                color_ = color;
                break;
        case 2: color.setRgb(37,219,24);
                color_ = color;
                break;
        case 3: color.setRgb(219,24,203);
                color_ = color;
                break;
        case 4: color.setRgb(24,209,219);
                color_ = color;
                break;
    }
}

QRectF Ship::boundingRect() const
{
    return QRectF(x_, y_, 20, 20);
}

QPainterPath Ship::shape() const
{
    QPainterPath path;
    path.addEllipse(x_, y_, 20, 20);
    return path;
}


void Ship::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QBrush b = painter->brush();
    painter->setBrush(QBrush(color_.dark(option->state & QStyle::State_Sunken ? 120 : 100)));

    painter->drawRect(QRect(this->x_, this->y_, 20, 20));
    painter->setBrush(b);
}
