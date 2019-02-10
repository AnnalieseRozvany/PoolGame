#ifndef DUPLICATIONBALLDECORATOR_H
#define DUPLICATIONBALLDECORATOR_H
#include "balldecorator.h"

/**
 * @brief The DuplicationBallDecorator class is a little bouns decorator that duplicates when it hits things
 */
class DuplicationBallDecorator: public BallDecorator
{
public:
    DuplicationBallDecorator(Ball *b)
        :BallDecorator(b)
    {}
    /**
     * @brief changeVelocity this acts like the regular function but can also duplicate the ball whilst decreasing its size
     * @param deltaV
     * @return
     */
    ChangeInPoolGame changeVelocity(const QVector2D &deltaV) override;
    virtual Ball* clone() override { return new DuplicationBallDecorator(m_ball->clone()); }
};

#endif // DUPLICATIONBALLDECORATOR_H
