#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QWidget>
#include <QPaintEvent>
#include <QTimer>
#include <QMouseEvent>
#include "poolgame.h"
#include "memento.h"

/**
 * @brief The Dialog class starts up and displays a poolgame
 */
class Dialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Dialog constructor
     * @param game is a pointer to a PoolGame, this takes ownership of that pointer
     * @param parent is the parent widget
     */
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    /**
     * @brief starts the simulation
     */
    void start(PoolGame * game);

    /**
     * @brief draws the simulation
     */
    void paintEvent(QPaintEvent *);

    /**
     * @brief mousePressEvent just emits the mousePressed signal
     * @param event
     */
    void mousePressEvent(QMouseEvent *event);

    /**
     * @brief mousePressEvent just emits the mouseMoved signal
     * @param event
     */
    void mouseMoveEvent(QMouseEvent *event);

    /**
     * @brief mousePressEvent just emits a mouseReleased signal
     * @param event
     */
    void mouseReleaseEvent(QMouseEvent *event);

    /**
     * @brief keyPressEvent manages keyboard buttons pressed
     * @param event
     */
    void keyPressEvent(QKeyEvent *event);


    /**
     * @brief save the users move
     */
    void makeMove();


    /**
     * @brief undo last move
     */
    void undo();

    /**
     * @brief start a new game
     */
    void newGame();

    /**
     * @brief add a ball to cursor's current location
     */
    void newBall();

    /**
     * @brief alerts that stage 3 is being used
     */
    void stage3() { m_stage3 = true; }

signals:
    void mousePressed(QMouseEvent * event);
    void mouseMoved(QMouseEvent * event);
    int mouseReleased(QMouseEvent * event);
    void keyPress(QKeyEvent *event);

public slots:
    void runSimulationStep();

private:
    PoolGame * m_game;
    QTimer * m_framerateTimer;
    QTimer * m_timestepTimer;
    std::vector<Memento*> m_savedStates;
    Originator m_originator;
    bool m_stage3;
    int m_score;
    int m_ballsSize;
};

#endif // DIALOG_H
