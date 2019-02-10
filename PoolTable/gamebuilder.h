#ifndef GAMEBUILDER_H
#define GAMEBUILDER_H

#include <QJsonObject>
#include <vector>

#include "poolgame.h"
#include "ball.h"
#include "table.h"
#include "abstractfactory.h"

/**
 * @brief The GameBuilder class is used to build a PoolGame object, To do this it uses a specific factory to create the components.
 * To change the type of poolgame created simply provide a different factory
 */
class GameBuilder
{
public:
    /**
     * @brief GameBuilder creates a gameBuilder object
     * @param factory is a pointer to a concrete implementation of AbstractFactory, GameBuilder takes ownership of this pointer
     */
    GameBuilder(AbstractFactory *factory);
    virtual ~GameBuilder();

    /**
     * @brief adds a ball to the game
     * @param ballJSon is the json configuration for the ball
     */
    void addBall(const QJsonObject &ballJSon);

    /**
     * @brief builds the table for the game, this overwrites any previous calls to build table
     * @param tableJSon is the json configuration for the ball
     */
    void buildTable(const QJsonObject &tableJSon);
    /**
     * @brief getGame creates and returns a pointer to a PoolGame, the caller now has ownership of that pointer
     * @return pointer to the created poolgame
     */
    PoolGame* getGame();

private:
    std::vector<Ball*> m_balls;
    Table *m_table;
    AbstractFactory *m_factory;
};

#endif // GAMEBUILDER_H
