#include "stage1table.h"
#include "ball.h"

void Stage1Table::draw(QPainter &p)
{
    p.setPen(Qt::black);
    p.setBrush(QBrush(m_colour));
    p.drawRect(0,0,m_width,m_height);
}

ChangeInPoolGame Stage1Table::ballCollision(Ball *b)
{
    //are we outside the bounds horizontally and getting further away?
    //if so reverse x velocity
    if((b->position().x()<b->radius() && b->velocity().x()<0) || (b->position().x()>width()-b->radius() && b->velocity().x()>0))
        b->changeVelocity(QVector2D(-b->velocity().x()*2,0));

    //same but vertical
    if((b->position().y()<b->radius() && b->velocity().y()<0) || (b->position().y()>height()-b->radius() && b->velocity().y()>0))
        b->changeVelocity(QVector2D(0,-b->velocity().y()*2));

    return ChangeInPoolGame();
}
