#include "transform.h"

Transform::Transform()
{
    scale = ofVec3f(1, 1, 1);
}

ofVec3f Transform::getPosition()
{
    return position;
}

ofVec3f Transform::getScale()
{
    return scale;
}

void Transform::translate(float dx, float dy, float dz)
{
    position.x += dx;
    position.y += dy;
    position.z += dz;
}

void Transform::reScale(float x, float y, float z)
{
    scale.x *= x;
    scale.y *= y;
    scale.z *= z;
}
