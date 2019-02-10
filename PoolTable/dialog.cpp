#include "dialog.h"

#include <QPainter>
#include <QSize>

#include <stdio.h>
#include <iostream>
#include "stage2ball.h"
#include "cueballdecorator.h"


constexpr float fps = 60;
constexpr float timeStep = 0.01;

Dialog::Dialog(QWidget *parent)
    :QDialog(parent),m_game(nullptr),m_framerateTimer(new QTimer()),m_timestepTimer(new QTimer()), m_score(1), m_stage3(false)
{


}

void Dialog::start(PoolGame *game)
{
    m_game = game;
    makeMove(); //Add starting positions
    m_ballsSize = m_game->getBalls().size();
    this->setMinimumSize(m_game->size());
    this->resize(m_game->size());
    connect(m_framerateTimer,SIGNAL(timeout()),this,SLOT(update()));
    connect(m_timestepTimer,SIGNAL(timeout()),this,SLOT(runSimulationStep()));
    m_framerateTimer->start(1000/fps);
    m_timestepTimer->start(1000*timeStep);
}

void Dialog::makeMove()
{
     m_score-=1;
    std::vector<Ball*>* balls = new std::vector<Ball*>();
    std::vector<Ball*> ballsToCopy = std::vector<Ball*>();
    if (m_savedStates.size() == 1) { // No moves left to undo
        ballsToCopy = *m_savedStates[0]->getSavedState();
    } else { // Starting game and Normal Move
        ballsToCopy = m_game->getBalls();
    }
    for (Ball* i : m_game->getBalls()) {
        balls->push_back(i->clone());
    }
    m_originator.set(balls);
    m_originator.set(m_score);
    m_savedStates.push_back(m_originator.saveToMomento());
}

void Dialog::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    if (!m_stage3) {
        m_game->draw(p);
        return;
    }

    if (m_ballsSize > m_game->getBalls().size()) {
        m_score += (m_ballsSize - m_game->getBalls().size())*100;
    }

    m_ballsSize = m_game->getBalls().size();

    if (m_game->getBalls().at(0)->colour() != "white") {
        p.setPen("black");
        p.setFont(QFont("Impact", 100, QFont::Bold));
        p.drawText(rect(), Qt::AlignCenter, "GAME OVER >:(");
        p.setFont(QFont("Comic Sans", 40));
        QString s = "Your Final Score: " + QString::number(m_score-100) + "\nDon't sink the white ball! Press 'n' for new game.";
        p.drawText(rect(), Qt::AlignTop+Qt::AlignHCenter, "✿༼◕_◕༽ ~Sink Da Ballz~ (◕‿◕)✿");
        p.setFont(QFont("Arial", 20));
        p.drawText(rect(), Qt::AlignBottom+Qt::AlignHCenter, s);
    } else  if ((m_game->getBalls().size() == 1 && m_game->getBalls().at(0)->colour() == "white") || m_game->getBalls().empty()) {
        p.setPen("black");
        p.setFont(QFont("Impact", 100, QFont::Bold));
        p.drawText(rect(), Qt::AlignCenter, "YOU WON!!!1!");
        p.setFont(QFont("Comic Sans", 40));
        QString s = "Your Final Score: " + QString::number(m_score);
        p.drawText(rect(), Qt::AlignTop+Qt::AlignHCenter, "✿༼◕_◕༽ ~Sink Da Ballz~ (◕‿◕)✿");
        p.setFont(QFont("Arial", 20));
        p.drawText(rect(), Qt::AlignBottom+Qt::AlignHCenter, s);
    } else {
        m_game->draw(p);
        p.setPen("white");
        p.setFont(QFont("Comic Sans", 30));
        QString s = "~ Score: " + QString::number(m_score) + " ~";
        p.drawText(rect(), Qt::AlignTop+Qt::AlignHCenter, "✿༼◕_◕༽ ~Sink Da Ballz~ (◕‿◕)✿");
        p.setFont(QFont("Comic Sans", 20));
        p.drawText(rect(), Qt::AlignBottom+Qt::AlignHCenter, s);
    }



}

void Dialog::mousePressEvent(QMouseEvent *event)
{
    emit mousePressed(event);
}

void Dialog::mouseMoveEvent(QMouseEvent *event)
{
    emit mouseMoved(event);
}

void Dialog::mouseReleaseEvent(QMouseEvent *event)
{
    emit mouseReleased(event);
}

void Dialog::keyPressEvent(QKeyEvent *event)
{
    if (!m_stage3) {
        return;
    }
    if (event->key() == Qt::Key_R) { // press R to undo move
        undo();
    } else if (event->key() == Qt::Key_S) { // number of moves
        std::cout << m_savedStates.size()-1 << std::endl;
    } else if (event->key() == Qt::Key_B) {
        newBall();
    } else if (event->key() == Qt::Key_N) {
        newGame();
    } else if (event->key() == Qt::Key_X) { // some balls explode, this is cheating tho
        m_game->explode();
        m_ballsSize = m_game->getBalls().size();
    } else if (event->key() == Qt::Key_P) { // create pocket
        QPoint p = mapFromGlobal(QCursor::pos());
        m_game->getTable()->newPocket(p);
    }
}

void Dialog:: undo()
{
    CueBallDecorator* c = (CueBallDecorator*)m_game->getBalls().at(0);
    c->deactivate();
    if (m_savedStates.size() == 1) {
        makeMove();
    } else {
        m_score = m_savedStates[m_savedStates.size()-1]->getScore();
        m_score-=5;
    }
    m_game->setBalls(*m_savedStates[m_savedStates.size()-1]->getSavedState());
    c = (CueBallDecorator*)m_game->getBalls().at(0);
    c->activate();
    m_savedStates.pop_back();
}

void Dialog:: newGame()
{
    while (m_savedStates.size() > 1) {
        m_savedStates.pop_back();
    }
    m_game->setBalls(*m_savedStates[0]->getSavedState());
    CueBallDecorator* c = (CueBallDecorator*)m_game->getBalls().at(0);
    c->deactivate();
    makeMove();
    m_game->setBalls(*m_savedStates[1]->getSavedState());
    c = (CueBallDecorator*)m_game->getBalls().at(0);
    c->activate();
    m_score = 0;
    m_ballsSize = m_game->getBalls().size();
}

void Dialog::newBall()
{
    QPoint p = mapFromGlobal(QCursor::pos());

    std::vector<Ball*> ballz = std::vector<Ball*>();
    std::vector<Ball*> balls = std::vector<Ball*>();
    CompositeBall* b = new CompositeBall();
    for (int i = 0; i < 4; i++) {
        ballz = std::vector<Ball*>();
        SimpleStage2Ball* s = new SimpleStage2Ball(QVector2D(-5,0), QVector2D(0,0), 5, 0.5, "aqua", 1e4);
        ballz.push_back(s);
        s = new SimpleStage2Ball(QVector2D(5,0), QVector2D(0,0), 5, 0.5, "aqua", 1e4);
        ballz.push_back(s);
        s = new SimpleStage2Ball(QVector2D(0,-5), QVector2D(0,0), 5, 0.5, "#ffccff", 1e4);
        ballz.push_back(s);
        s = new SimpleStage2Ball(QVector2D(0,5), QVector2D(0,0), 5, 0.5, "black", 1e4);
        ballz.push_back(s);
        if (i == 0) {
            b = new CompositeBall(QVector2D(-10,0),QVector2D(0,0), 10, 1, "black", 1e5, ballz, 4);
        } else if (i == 1) {
            b = new CompositeBall(QVector2D(10,0),QVector2D(0,0), 10, 1, "black", 1e5, ballz, 4);
        } else if (i == 2) {
            b = new CompositeBall(QVector2D(0,10),QVector2D(0,0), 10, 1, "black", 1e5, ballz, 4);
        } else if (i == 3) {
            b = new CompositeBall(QVector2D(0,-10),QVector2D(0,0), 10, 1, "black", 1e5, ballz, 4);
        }
        balls.push_back(b);
    }
    b = new CompositeBall(QVector2D(p),QVector2D(0,0), 20, 1, "#ffccff", 1e5, balls, 4);
    m_game->addBall(b);
    m_ballsSize++;
}


Dialog::~Dialog()
{
    delete m_game;
    delete m_framerateTimer;
    delete m_timestepTimer;
}

void Dialog::runSimulationStep()
{
    m_game->simulateTimeStep(timeStep);
}
