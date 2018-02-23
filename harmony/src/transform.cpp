#include "transform.h"

ofVec3f Transform::getPosition()
{
    return position;
}

void Transform::translate(float dx, float dy, float dz)
{
    position.x += dx;
    position.y += dy;
    position.z += dz;
}
