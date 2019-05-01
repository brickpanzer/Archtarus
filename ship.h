#ifndef SHIP_H
#define SHIP_H

#include <QObject>
#include <QGraphicsItem>

class Ship : public QObject , public QGraphicsItem
{
    Q_OBJECT
public:
    Ship(const int x, const int y, const int player_id);

    int get_x() const { return x_; }  // inline member function
    int get_y() const { return y_; }  // inline member function

    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
private:
    int x_;
    int y_;
    int player_id_;
    QColor color_;
};

#endif // SHIP_H
