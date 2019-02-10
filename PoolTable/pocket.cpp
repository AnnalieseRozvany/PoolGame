#include "pocket.h"
void Pocket::draw(QPainter &p)
{
    p.setPen(Qt::black);
    p.setBrush(QBrush(Qt::black));
    p.drawEllipse(m_position.toPointF(),m_radius,m_radius);
}
