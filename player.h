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
};

#endif // PLAYER_H
