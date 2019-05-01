#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsItem>

#include "planet.h"
#include "ship.h"

class Player : public QObject , public QGraphicsItem
{
    Q_OBJECT
public:
    Player(const int x, const int y, const int player_num_);

    int get_x() const { return x_; }  // inline member function
    int get_y() const { return y_; }  // inline member function
    int get_planets_() const { return planets_.size(); }
    std::vector<Planet*> planets(){ return planets_; }
    double get_parts() const { return parts_; }
    double get_fuel() const { return fuel_; }
    double get_people() const { return people_; }
    int get_fleet_lvl() const { return fleet_lvl_; }
    QColor get_player_color() const { return player_color_; }

    void call_turn();
    void add_planet(Planet *p);
    void add_ship(Ship *s);
    void remove_planet(Planet *p);
    bool level_fleet();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
private:
    int x_;
    int y_;
    int player_num_;
    QColor player_color_;
    double parts_;
    double fuel_;
    double people_;
    int fleet_lvl_;
    std::vector<Planet*> planets_;
    std::vector<Ship*> fleet_;
};

#endif // PLAYER_H
