#ifndef POCKET_H
#define POCKET_H

#include <QPainter>
#include <QVector2D>
#include <QObject>
#include <iostream>

/**
 * @brief The Pocket class simply represents a pocket on the table
 */
class Pocket : public QObject
{
public:
    Pocket() : m_position(QVector2D(0,0)), m_radius(0) {}
    Pocket(QPoint pos, float r) : m_position(QVector2D(pos)), m_radius(r) {}
    Pocket(QVector2D pos, float r)
        :m_position(pos),m_radius(r) {}
    virtual void draw(QPainter &p);
    /**
     * @brief returns if the ball is encompassed by the pocket
     */
    virtual bool encompassed(QVector2D circleCentre, float r) { return (circleCentre-m_position).length() + r < m_radius;}
    virtual bool portal() {return false;}
    virtual QVector2D transport() {return m_position;}
    QVector2D pos() {return m_position;}
    float radius() {return m_radius;}

private:
    QVector2D m_position;
    float m_radius;

};

class PocketPortalDecorator : public Pocket
{
public:
    PocketPortalDecorator(Pocket* pocket) : m_pocket(pocket) {}
    bool portal() override {return true;}
    virtual void draw(QPainter &p) override {m_pocket->draw(p);}
    virtual bool encompassed(QVector2D circleCentre, float r) override { return m_pocket->encompassed(circleCentre, r);}
    Pocket* pocket() {return m_pocket;}
private:
    Pocket* m_pocket;
};

/**
 * @brief Entry Poral
 */
class InPortal : public PocketPortalDecorator
{
public:
    InPortal(Pocket* pocket, QVector2D out, QVector2D location, float rad): PocketPortalDecorator(pocket), m_out(out), m_location(location), m_rad(rad) {}
    virtual QVector2D transport() override {return m_out;}
    virtual void draw(QPainter &p) override {
        QPen q = QPen("#82FFFF");
        q.setWidth(2);
        p.setPen(q);
        p.setBrush(QBrush(Qt::black));
        p.drawEllipse(m_location.toPointF(),m_rad,m_rad);
        QPoint x = QPoint(m_location.x()-6, m_location.y()+5);
        p.drawText(x, "IN");
//        std::cout << m_location.x() << " " << std::endl;
    }
private:
    QVector2D m_out;
    QVector2D m_location;
    float m_rad;
};

/**
 * @brief Exit Portal
 */
class OutPortal : public PocketPortalDecorator
{
public:
    OutPortal(Pocket* pocket, QVector2D location, float rad): PocketPortalDecorator(pocket), m_location(location), m_rad(rad) {}
    virtual void draw(QPainter &p) override{
        QPen q = QPen("#82FFFF");
        q.setWidth(2);
        p.setPen(q);
        p.setBrush(QBrush(Qt::black));
        p.drawEllipse(m_location.toPointF(),m_rad,m_rad);
        QPoint x = QPoint(m_location.x()-13, m_location.y()+5);
        p.drawText(x, "OUT");
    }
    virtual bool encompassed(QVector2D circleCentre, float r) override {
        (void)circleCentre;
        (void)r;
        return false;
    }
private:
    QVector2D m_location;
    float m_rad;
};

#endif // POCKET_H
