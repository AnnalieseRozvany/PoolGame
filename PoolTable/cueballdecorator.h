#ifndef CUEBALLDECORATOR_H
#define CUEBALLDECORATOR_H
#include "balldecorator.h"

#include "dialog.h"

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QObject>

/**
 * @brief The CueBallDecorator class is the decorator that turns a ball into a cue ball
 */
class CueBallDecorator : public BallDecorator, public QObject
{
public:
    /**
     * @brief CueBallDecorator decorates a ball to be used as a cue ball
     * @param b is the ball to be decorated
     * @param parent is the parent Dialog, this is used to connect to the signals it emits
     */
    CueBallDecorator(Ball * b, Dialog * parent);
    ~CueBallDecorator() {disconnect(m_parent,&Dialog::mouseReleased,this,&CueBallDecorator::mouseReleased);}
    void draw(QPainter &p) override;
    virtual Ball* clone() override {
        CueBallDecorator* c = new CueBallDecorator(m_ball->clone(), m_parent);
        c->deactivate();
        return (Ball*)c;
    }
    void deactivate() { m_active = 0;}
    void activate() { m_active = 1;}


public slots:
    void mousePressed(QMouseEvent * event);
    void mouseMoved(QMouseEvent * event);
    void mouseReleased(QMouseEvent * event);


private:
    QVector2D endpoint;
    QVector2D mousePos;
    bool clicked;
    Dialog* m_parent;
    int m_active;
};

#endif // CUEBALLDECORATOR_H
