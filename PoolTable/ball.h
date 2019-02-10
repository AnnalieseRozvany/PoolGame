#ifndef BALL_H
#define BALL_H

#include <QPainter>
#include <QVector2D>
#include <QColor>

#include "changeinpoolgame.h"


/**
 * @brief The Ball class containes the logic and member variables of a circle representing a ball
 * concrete subclasses should override the draw function to enable drawing the ball
 */
class Ball
{
public:
    Ball() {}
    Ball(QVector2D position, QVector2D velocity, float radius, float mass, QColor colour) :
        m_position(position), m_velocity(velocity), m_radius(radius), m_mass(mass), m_colour(colour) {}
    virtual ~Ball() {}

    virtual const QVector2D &position()const{return m_position;}
    virtual const QVector2D &velocity()const{return m_velocity;}
    virtual float radius()const{return m_radius;}
    virtual float mass()const{return m_mass;}
    virtual int type() {return 0;}

    virtual void setPosition(const QVector2D &newPosition){m_position = newPosition;}
    /**
     * @brief setVelocity sets the velocity manually to a value.
     * This should only be used to initialize the balls starting velocity
     * and set it to zero if it is small enough, otherwise use changeVelocity
     * @param newVelocity
     */
    virtual void setVelocity(const QVector2D &newVelocity){m_velocity = newVelocity;}
    virtual void setRadius(float newRadius){m_radius = newRadius;}
    virtual void setMass(float newMass){m_mass = newMass;}
    virtual const QColor & colour(){return m_colour;}

    virtual void changePosition(const QVector2D &deltaX){m_position += deltaX;}
    virtual ChangeInPoolGame changeVelocity(const QVector2D &deltaV){m_velocity += deltaV; return ChangeInPoolGame();}
    virtual void setColour(const QColor &newColour){m_colour = newColour;}
    /**
     * @brief draws the ball using the provided painter
     * @param p is the painter that is used to draw the object
     */
    virtual void draw(QPainter & p) = 0;

    /**
     * @brief moves the ball based on its current velocity
     * @param timestep is the ammount of time it should move for
     */
    virtual void move(float timestep){changePosition(m_velocity*timestep);}

    virtual bool collidesWith(Ball * other) {return (this->position()-other->position()).length() < this->radius()+other->radius();}

    /**
     * @brief Prototype cloning interface
     */
    virtual Ball* clone() = 0;
    virtual ChangeInPoolGame explodeBall() { return ChangeInPoolGame(std::vector<Ball*>(), std::vector<Ball*>());}

protected:
    QVector2D m_position;
    QVector2D m_velocity;
    float m_radius;
    float m_mass;
    QColor m_colour;

};
#endif // BALL_H
