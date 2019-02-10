#ifndef STAGE3TABLE_H
#define STAGE3TABLE_H


#include <QColor>
#include <QPainter>
#include <vector>
#include <QVector2D>

#include "table.h"
#include "pocket.h"
/**
 * @brief The Stage2Table class is a concrete version of the Table class specific to stage one of the assignment
 */
class Stage3Table : public Table
{
public:
    Stage3Table() : Table(0,0,0), m_colour("white"), m_pockets(std::vector<Pocket*>()) {}
    Stage3Table(float width, float height,float friction, const QColor &colour, std::vector<Pocket*> pockets)
        :Table(width,height,friction),m_colour(colour),m_pockets(pockets)
    {}

    void newPocket(QPoint pos) {
        m_pockets.push_back(new Pocket(pos, 20));
    }

    // Table interface
public:
    /**
     * @brief draw the table, it is just a rectangle of width() and height()
     * with the colour set in the constructor
     * @param p the painter used to draw the table
     */
    void draw(QPainter &p);

private:
    QColor m_colour;
    std::vector<Pocket*> m_pockets;

    // Table interface
public:
    ChangeInPoolGame ballCollision(Ball *b);
};

#endif // STAGE3TABLE_H
