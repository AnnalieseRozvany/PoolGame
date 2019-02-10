#ifndef BALLDECORATOR_H
#define BALLDECORATOR_H
#include "ball.h"

class BallDecorator : public Ball
{
public:
    BallDecorator(Ball *b)
        :m_ball(b)
    {}
    ~BallDecorator()
    {
        delete m_ball;
    }

protected:
    Ball *m_ball;

    // Ball interface
public:
    float mass() const {return m_ball->mass();}
    void changePosition(const QVector2D &deltaX) {m_ball->changePosition(deltaX);}
    ChangeInPoolGame changeVelocity(const QVector2D &deltaV)
    {
        ChangeInPoolGame change = m_ball->changeVelocity(deltaV);
        for(size_t i = 0; i < change.m_ballsToRemove.size();++i)
        {
            if(change.m_ballsToRemove[i]==m_ball)
                change.m_ballsToRemove[i] = this;
        }
        return change;
    }
    void draw(QPainter &p) {m_ball->draw(p);}
    void move(float timestep) {m_ball->move(timestep);}
    const QVector2D &position() const {return m_ball->position();}
    const QVector2D &velocity() const {return m_ball->velocity();}
    float radius() const {return m_ball->radius();}
    void setPosition(const QVector2D &newPosition) {return m_ball->setPosition(newPosition);}
    void setVelocity(const QVector2D &newVelocity) {return m_ball->setVelocity(newVelocity);}
    void setRadius(float newRadius) {return m_ball->setRadius(newRadius);}
    void setMass(float newMass) {return m_ball->setMass(newMass);}
    const QColor &colour() {return m_ball->colour();}
    void setColour(const QColor &newColour) {return m_ball->setColour(newColour);}
    bool collidesWith(Ball *other) {return m_ball->collidesWith(other);}
};

#endif // BALLDECORATOR_H
