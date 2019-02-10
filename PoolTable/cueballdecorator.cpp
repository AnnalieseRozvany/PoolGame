#include "cueballdecorator.h"
#include "iostream"
CueBallDecorator::CueBallDecorator(Ball *b, Dialog *parent)
    :BallDecorator(b),clicked(false), m_parent(parent), m_active(1)
{
    //connect dialog signals to cueball slots so that this class is notified when the mouse is used
    connect(parent,&Dialog::mousePressed,this,&CueBallDecorator::mousePressed);
    connect(parent,&Dialog::mouseMoved,this,&CueBallDecorator::mouseMoved);
    connect(parent,&Dialog::mouseReleased,this,&CueBallDecorator::mouseReleased);
}

void CueBallDecorator::draw(QPainter &p)
{
    m_ball->draw(p);
    if(clicked)
        p.drawLine(mousePos.toPointF(),m_ball->position().toPointF());
}

void CueBallDecorator::mousePressed(QMouseEvent *event)
{
    if(velocity().lengthSquared()<0.001 && (QVector2D(event->pos())-position()).length() < radius() && m_active)
    {
        clicked = true;
        mousePos = QVector2D(event->pos());
    }
}

void CueBallDecorator::mouseMoved(QMouseEvent *event)
{
    if(clicked && m_active)
    {
        mousePos = QVector2D(event->pos());
    }

}

void CueBallDecorator::mouseReleased(QMouseEvent *event)
{
    if(clicked && m_active)
    {
        clicked = false;
        m_parent->makeMove(); //save the current ball positions to be able to return to
        setVelocity(4*(m_ball->position()-mousePos));
    }
}
