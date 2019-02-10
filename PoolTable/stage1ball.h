#ifndef STAGEONEBALL_H
#define STAGEONEBALL_H

#include <QColor>
#include <QPainter>

#include "ball.h"

/**
 * @brief The Stage1Ball class is a concrete version of the Ball class specific to stage one of the assignment
 */
class Stage1Ball : public Ball
{
public:
    Stage1Ball();
    Stage1Ball(QVector2D position, QVector2D velocity, float radius, float mass, QColor colour) :
        Ball(position, velocity, radius, mass, colour) {}
    virtual Ball* clone() override { return new Stage1Ball(m_position, m_velocity, m_radius, m_mass, m_colour); }
    // Ball interface
public:
    /**
     * @brief draw the ball
     * @param painter to use to draw the ball
     */
    void draw(QPainter &p) override;
};


#endif // STAGEONEBALL_H
