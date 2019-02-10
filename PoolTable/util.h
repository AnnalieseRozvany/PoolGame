#ifndef UTIL_H
#define UTIL_H
#include <QVector2D>
#include <QJsonValue>
#include <vector>
/**
 * @brief converts a value that is an object of the form {"x":float,"y":float} into a QVector2D with the appropriate values
 * @param v is the QJsonValue to convert
 * @return the QVector2D that is encoded in the JSon
 */
QVector2D QJsonValueToVector2D(const QJsonValue &v, float defaultX = 0, float defaultY = 0);

/**
 * @brief circleRectangleIntersection calculates if there is an intersection between the provided circle and rectangle
 * @param circleCentre
 * @param circleRadius
 * @param rectCenter
 * @param rectDimensions
 * @return true if there is any overlap between the two shapes, false otherwise
 */
bool circleRectangleIntersection(const QVector2D &circleCentre,float circleRadius, const QVector2D &rectCenter,const QVector2D &rectDimensions);

/**
 *merge two vectors together such that the resulting vector is the union of the two provided vecotrs
 */
template <typename T>
std::vector<T> mergeVectors(const std::vector<T> &vecA,const std::vector<T> &vecB)
{
    std::vector<T> result = vecB;
    for(T a: vecA)
    {
        bool duplicate = false;
        for(T b: vecB)
        {
            if(a == b)
            {
                duplicate = true;
                break;
            }
        }
        if(!duplicate)
        {
            result.push_back(a);
        }
    }
    return result;
}

#endif // UTIL_H
