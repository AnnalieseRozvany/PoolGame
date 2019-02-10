#include "stage1factory.h"

#include "stage1ball.h"
#include "stage1table.h"
#include "util.h"

#include <QColor>
#include <QVector2D>
#include <QJsonObject>
#include <QJsonValue>
#include <QString>

Ball *Stage1Factory::makeBall(const QJsonObject &config)
{
    //we kind of use a builder style setx, sety, etc, here but just because
    //it is easier than setting all the stuff in the constructor
    //this means we don't need any of the common stuff cluttering the stageOneBall class
    Stage1Ball * ball = new Stage1Ball();

    ball->setVelocity(QJsonValueToVector2D(config["velocity"]));
    ball->setRadius(config["radius"].toDouble(10));
    ball->setPosition(QJsonValueToVector2D(config["position"],ball->radius(),ball->radius()));
    ball->setMass(config["mass"].toDouble(1.0));
    ball->setColour(config["colour"].toString());

    return ball;
}

Table *Stage1Factory::makeTable(const QJsonObject &config)
{
    //not really worth doing the builder style with only 3 variables
    QVector2D dimensions = QJsonValueToVector2D(config["size"],300,600);
    float friction = config["friction"].toDouble();
    QColor colour = QColor(config["colour"].toString());

    return new Stage1Table(dimensions.x(),dimensions.y(),friction,colour);

}
