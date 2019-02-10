#ifndef STAGE2FACTORY_H
#define STAGE2FACTORY_H
#include <QJsonObject>
#include <QVector2D>

#include "abstractfactory.h"
#include "ball.h"
#include "table.h"

class Dialog;

/**
 * @brief The Stage2Factory class creates concrete objects for stage one
 */
class Stage2Factory : public AbstractFactory
{
public:
    Stage2Factory(Dialog * parent):
    cueBallSet(false), dialog(parent){}

    // AbstractFactory interface
public:
    /**
     * @brief makes and returns a stageOneBall
     * @param config is the configuration for the ball in json format
     * @return a pointer to a valid stage2Ball
     */
    Ball *makeBall(const QJsonObject &config);

    /**
     * @brief makes and returns a stageOneTable
     * @param config is the configuration for the table in json format
     * @return a pointer to a valid stage2Table
     */
    Table *makeTable(const QJsonObject &config);

private:
    /**
     * @brief makeBallBasedOnParent creates a ball with defaults and bounds based upon the parent
     * @param config
     * @param parent is the parent ball, if it is null then it is a base ball
     * @return a pointer to a ball
     */
    Ball *makeBallBasedOnParent(const QJsonObject &config, Ball* parent = nullptr) const;

    QVector2D m_tableDimensions;
    bool cueBallSet;
    Dialog * dialog;
};
#endif // STAGE2FACTORY_H
