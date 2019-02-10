#ifndef MEMENTO_H
#define MEMENTO_H

#include "poolgame.h"

/**
 * @brief The Memento class stores the states of the game, which is the balls.
 */
class Memento
{
public:
    Memento(std::vector<Ball*>* state, int score) : m_state(state), m_score(score) {}
    std::vector<Ball*>* getSavedState() {return m_state;}
    int getScore() {return m_score;}
private:
    std::vector<Ball*>* m_state;
    friend class Originator;
    int m_score;
};

/**
 * @brief The Originator class gives access to the Memento class
 */
class Originator
{
public:
    Originator() : m_state(new std::vector<Ball*>()), m_score(0) {}
    void set(std::vector<Ball*>* state) { m_state = state; }
    void set(int score) {m_score = score;}
    Memento* saveToMomento(){ return new Memento(m_state, m_score);}
    void restoreFromMomento(Memento memento) {
        m_state = memento.getSavedState();
        m_score = memento.getScore();
    }

private:
    std::vector<Ball*>* m_state;
    int m_score;
};

#endif // MEMENTO_H
