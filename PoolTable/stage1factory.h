#ifndef STAGEONEFACTORY_H
#define STAGEONEFACTORY_H

#include <QJsonObject>

#include "abstractfactory.h"
#include "ball.h"
#include "table.h"

/**
 * @brief The Stage1Factory class creates concrete objects for stage one
 */
class Stage1Factory : public AbstractFactory
{
public:
    Stage1Factory(){}

    // AbstractFactory interface
public:
    /**
     * @brief makes and returns a stageOneBall
     * @param config is the configuration for the ball in json format
     * @return a pointer to a valid stage1Ball
     */
    Ball *makeBall(const QJsonObject &config);

    /**
     * @brief makes and returns a stage1Table
     * @param config is the configuration for the table in json format
     * @return a pointer to a valid stageOneTable
     */
    Table *makeTable(const QJsonObject &config);
};

#endif // STAGEONEFACTORY_H
