#include "util.h"

#include <QJsonObject>
#include <cmath>


bool circleRectangleIntersection(const QVector2D &circleCentre, float circleRadius, const QVector2D &rectCenter, const QVector2D &rectDimensions)
{
    //get absolute distance between centre points
    QVector2D distance = circleCentre-rectCenter;
    distance.setX(fabs(distance.x()));
    distance.setY(fabs(distance.y()));

    QVector2D rectDimensionsHalved = rectDimensions/2;

    if (distance.x() > (rectDimensionsHalved.x() + circleRadius)||
            distance.y() > (rectDimensionsHalved.y() + circleRadius))
    {
        return false;
    }

    if (distance.x() <= (rectDimensionsHalved.x()) ||
            distance.y() <= (rectDimensionsHalved.y()))
    {
        return true;
    }

    float cornerDistance_sq = (distance-rectDimensionsHalved).lengthSquared();
    return (cornerDistance_sq <= (circleRadius*circleRadius));
}

QVector2D QJsonValueToVector2D(const QJsonValue &v, float defaultX, float defaultY)
{
    return QVector2D(v.toObject()["x"].toDouble(defaultX),v.toObject()["y"].toDouble(defaultY));
}
