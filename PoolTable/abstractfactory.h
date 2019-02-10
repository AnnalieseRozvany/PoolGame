#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include <QJsonObject>

#include "ball.h"
#include "table.h"

/**
 * @brief The AbstractFactory class creates instances of balls and tables
 */
class AbstractFactory
{
public:
    AbstractFactory() {}
    /**
     * @brief makeBall creates a ball from the provided json object
     * @param config a json object containing the ball configuration
     * @return the created ball that will always be in a valid state
     * no matter the provided json
     */
    virtual Ball* makeBall(const QJsonObject &config) = 0;

    /**
     * @brief makeBall creates a table from the provided json object
     * @param config a json object containing the table configuration
     * @return the created table that will always be in a valid state
     * no matter the provided json
     */
    virtual Table* makeTable(const QJsonObject &config) = 0;
};

#endif // ABSTRACTFACTORY_H
