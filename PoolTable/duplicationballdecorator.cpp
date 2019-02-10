#include "duplicationballdecorator.h"
#include "stage1ball.h"

ChangeInPoolGame DuplicationBallDecorator::changeVelocity(const QVector2D &deltaV)
{
    ChangeInPoolGame change = BallDecorator::changeVelocity(deltaV);
    bool deleted = std::find(change.m_ballsToRemove.begin(),change.m_ballsToRemove.end(),this) != change.m_ballsToRemove.end();

    //if the ball is big enough and hits hard enough it will duplicate into two
    if(radius()>1&&deltaV.lengthSquared()>velocity().lengthSquared()&&!deleted)
    {
        setRadius(radius()/2);
        setMass(mass()/2);
        Ball * duplicateBall = new Stage1Ball();
        duplicateBall->setColour(colour());
        duplicateBall->setMass(mass());
        duplicateBall->setPosition(position());
        duplicateBall->setRadius(radius());
        duplicateBall->setVelocity(velocity()/2);
        change.m_ballsToAdd.push_back(new DuplicationBallDecorator(duplicateBall));
    }
    return change;
}
