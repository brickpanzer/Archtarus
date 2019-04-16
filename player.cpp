#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>
#include <QDebug>
#include <QRandomGenerator>

#include "player.h"

Player::Player(const int x, const int y, const int num): x_(x), y_(y), player_num_(num)
{

}

QRectF Player::boundingRect() const
{
    return QRectF(x_, y_, 20, 20);
}

QPainterPath Player::shape() const
{
    QPainterPath path;
    path.addEllipse(x_, y_, 20, 20);
    return path;
}


void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QColor color_;
    color_.setRgb(0,0,0);

    QBrush b = painter->brush();
    painter->setBrush(QBrush(color_.dark(option->state & QStyle::State_Sunken ? 120 : 100)));

    painter->drawEllipse(QRect(this->x_, this->y_, 20, 20));
    painter->setBrush(b);
}
