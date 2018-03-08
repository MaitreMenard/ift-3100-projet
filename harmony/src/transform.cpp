#include "transform.h"

Transform::Transform()
{
    scale = ofVec3f(1, 1, 1);
}

ofVec3f Transform::getPosition()
{
    return position;
}

ofQuaternion Transform::getRotation()
{
	return rotation;
}

void Transform::getRotate(float & angle, float & x, float & y, float & z)
{
    rotation.getRotate(angle, x, y, z);
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

void Transform::rotate(float degrees, float x, float y, float z)
{
    rotation *= ofQuaternion(degrees, ofVec3f(x, y, z));
}

void Transform::setRotation(float thetaX, float thetaY, float thetaZ)
{
    rotation.makeRotate(thetaX, ofVec3f(1, 0, 0), thetaY, ofVec3f(0, 1, 0), thetaZ, ofVec3f(0, 0, 1));
}

void Transform::reScale(float x, float y, float z)
{
    scale.x *= x;
    scale.y *= y;
    scale.z *= z;
}
