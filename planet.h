#ifndef PLANET_H
#define PLANET_H

#include <QObject>
#include <QGraphicsItem>

class Planet : public QObject , public QGraphicsItem
{
    Q_OBJECT
public:
    Planet(const int x, const int y, const int size);

    int get_x() const { return x_; }  // inline member function
    int get_y() const { return y_; }  // inline member function

    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
private:
    int x_;
    int y_;
//    int x_offset_;
//    int y_offset_;
    int size_;
    int width_;
    QColor color_;
    int parts_;
    int fuel_;
    int people_;
    int owner_id_;
    int defense_lvl_;
};

#endif // PLANET_H
