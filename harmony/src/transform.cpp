#include "transform.h"


Transform::Transform(const Transform &other)
{
    position = ofVec3f(other.position);
    rotation = ofQuaternion(other.rotation);
    scale = ofVec3f(other.scale);
}

Transform::Transform()
{
    position = ofVec3f(0, 0, 0);
    rotation.makeRotate(0, ofVec3f(1, 0, 0), 0, ofVec3f(0, 1, 0), 0, ofVec3f(0, 0, 1));
    scale = ofVec3f(1, 1, 1);
}

ofVec3f Transform::getPosition() const
{
    return position;
}

void Transform::setPosition(ofVec3f position)
{
    this->position = position;
}

void Transform::translate(float dx, float dy, float dz)
{
    position += ofVec3f(dx, dy, dz);
}

ofQuaternion Transform::getRotation() const
{
    return rotation;
}

void Transform::getRotate(float & angle, float & x, float & y, float & z)
{
    rotation.getRotate(angle, x, y, z);
}

void Transform::setRotation(float x, float y, float z)
{
    rotation = ofQuaternion(x, ofVec3f(1, 0, 0), y, ofVec3f(0, 1, 0), z, ofVec3f(0, 0, 1));
}

void Transform::rotate(float degrees, float x, float y, float z)
{
    rotation *= ofQuaternion(degrees, ofVec3f(x, y, z));
}

ofVec3f Transform::getScale() const
{
    return scale;
}

void Transform::setScale(ofVec3f scale)
{
    this->scale = scale;
}

void Transform::reScale(float x, float y, float z)
{
    scale *= ofVec3f(x, y, z);
}

void Transform::applyToModelViewMatrix()
{
    ofTranslate(position);

    ofScale(scale);

    float angle, x, y, z;
    rotation.getRotate(angle, x, y, z);
    ofRotate(angle, x, y, z);
}

bool Transform::operator==(const Transform &obj1)
{
    if (position != obj1.position)
        return false;
    if (rotation != obj1.rotation)
        return false;
    if (scale != obj1.scale)
        return false;
    return true;
}

bool Transform::operator!=(const Transform &obj1)
{
    return !(*this == obj1);
}
