#ifndef STAGE2BALL_H
#define STAGE2BALL_H
#include <vector>

#include "ball.h"
#include "changeinpoolgame.h"
#include <cmath>
#include <iostream>

/**
 * @brief The Stage2Ball class is the component in the composite design pattern
 * it contains the general stage 2 quality strength
 */
class Stage2Ball : public Ball
{
public:
    Stage2Ball(){}
    Stage2Ball(QVector2D position, QVector2D velocity, float radius, float mass, QColor colour, float strength) : Ball(position, velocity, radius, mass, colour), m_strength(strength) {}
    void setStrength(float strength){m_strength = strength;}
    // Ball interface
    float strength() {return m_strength;}
    virtual Ball* clone() override { return new Stage2Ball(m_position, m_velocity, m_radius, m_mass, m_colour, m_strength); }
public:
    void draw(QPainter &p) override;

protected:
    float m_strength;
};

/**
 * @brief The CompositeBall class is the composite in the composite design pattern,
 * it stores a vector of children of type Stage2Ball. It can break apart to release these balls.
 */
class CompositeBall : public Stage2Ball
{
public:
    CompositeBall():m_containedMass(0)
    {
        Ball::setRadius(-1);
    }
    CompositeBall(QVector2D position, QVector2D velocity, float radius, float mass, QColor colour, float strength, std::vector<Ball*> containedBalls, float contained_mass):
        Stage2Ball(position, velocity, radius, mass, colour, strength), m_containedBalls(containedBalls), m_containedMass(contained_mass)
    {

    }
    virtual ~CompositeBall();

    int type() override {return 2;}

    /**
     * @brief changeVelocity changes the velocity of the ball, if it changes to fast it may break apart
     * @param deltaV the change in velocity
     * @return the change to the poolgame list of balls, if the ball breaks it will be added to the remove list
     * and its children will be added to the add list
     */
    ChangeInPoolGame changeVelocity(const QVector2D &deltaV) override;

    /**
     * @brief mass get the total mass of the composite ball wich is the sum of its mass and the mass of its children
     * @return
     */
    float mass() const override;

    /**
     * @brief draws the composite ball, if draw children is true it will also draw its children
     * @param p
     */
    void draw(QPainter &p) override;

    /**
     * @brief addBall to the composite
     * @param ball
     */
    void addBall(Ball* ball)
    {
        m_containedBalls.push_back(ball);
        m_containedMass += ball->mass();
    }

    float containedMass() { return m_containedMass;}

    /**
     * @brief setRadius sets the new radius of the ball, adjusting the radius of any children so they are stil contained
     * @param newRadius
     */
    void setRadius(float newRadius) override;

    std::vector<Ball*> containedBalls() { return m_containedBalls; }

    ChangeInPoolGame explodeBall() override {

        for(Ball * b: m_containedBalls)
        {
            std::cout << b->position().x() << " " << b->position().y() << std::endl;
            b->setVelocity(b->position()*10);
            b->setPosition(m_position+b->position());
        }
        ChangeInPoolGame change({this},std::move(m_containedBalls));
        m_containedBalls.clear();
        return change;
    }

    virtual Ball* clone() override
    {
        std::vector<Ball*> clonedChildren = std::vector<Ball*>();
        for (Ball* b : m_containedBalls) {
            clonedChildren.push_back(b->clone());
        }
        return new CompositeBall(m_position, m_velocity, m_radius, m_mass, m_colour, m_strength, clonedChildren, m_containedMass);
    }

protected:
    std::vector<Ball*> m_containedBalls;
    float m_containedMass;
    //here we decide whether or not to draw children
    bool drawChildren = true;
};

/**
 * @brief The SimpleStage2Ball class is the leaf in the composite design pattern,
 * all stage 2 balls that aren't composites are leaves
 */
class SimpleStage2Ball : public Stage2Ball
{
public:
    SimpleStage2Ball(){}
    SimpleStage2Ball(QVector2D position, QVector2D velocity, float radius, float mass, QColor colour, float strength) :
        Stage2Ball(position, velocity, radius, mass, colour, strength) {}
    int type() override {return 1;}
    ChangeInPoolGame changeVelocity(const QVector2D &deltaV) override;
    virtual Ball* clone() override { return new SimpleStage2Ball(m_position, m_velocity, m_radius, m_mass, m_colour, m_strength); }

};

#endif // STAGE2BALL_H
