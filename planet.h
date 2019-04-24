#ifndef PLANET_H
#define PLANET_H

#include <QObject>
#include <QGraphicsItem>

class Planet : public QObject , public QGraphicsItem
{
    Q_OBJECT
public:
    Planet(const int x, const int y,const int x_off, const int y_off, const int size);

    int get_x() const { return x_; }  // inline member function
    int get_y() const { return y_; }  // inline member function
    double get_parts() const { return parts_; }
    double get_fuel() const { return fuel_; }
    double get_people() const { return people_; }

    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
public slots:
    void ChangePlanetOwner(QColor color);
signals:
    void PlanetClicked(Planet * p);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
private:
    int x_;
    int y_;
    int x_offset_;
    int y_offset_;
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
