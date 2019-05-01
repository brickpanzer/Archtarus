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
    parts_ = 0.0;
    fuel_ = 0.0;
    people_ = 0.0;
    fleet_lvl_ = 0;
    std::vector<Planet*> p_tmp;
    std::vector<Ship*> s_tmp;
    fleet_ = s_tmp;
    planets_ = p_tmp;
    QColor color;
    switch(player_num_){
        case 1: color.setRgb(27,24,219);
                player_color_ = color;
                break;
        case 2: color.setRgb(37,219,24);
                player_color_ = color;
                break;
        case 3: color.setRgb(219,24,203);
                player_color_ = color;
                break;
        case 4: color.setRgb(24,209,219);
                player_color_ = color;
                break;
    }
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

void Player::call_turn()
{
    for(Planet * p : this->planets_){
        fuel_ += p->get_fuel();
        parts_ += p->get_parts();
        people_ += p->get_people();
    }
}

void Player::add_planet(Planet *p){
    planets_.push_back(p);
}

void Player::add_ship(Ship *s){
    fleet_.push_back(s);
}

void Player::remove_planet(Planet *p){
    int pos = 0;
    for(Planet *x: planets_){
        if(x->get_x() == p->get_x() && x->get_y() == p->get_y()){
            planets_.erase(planets_.begin() + pos);
        }
        pos++;
    }
}
