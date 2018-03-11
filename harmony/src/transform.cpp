#include "transform.h"


Transform::Transform(const Transform &transf)
{
    localPosition = ofVec3f(transf.getPosition());
    localRotation = ofQuaternion(transf.getRotation());
    localScale = ofVec3f(transf.getScale());
}

Transform::Transform()
{
    globalPosition = localPosition = ofVec3f(0, 0, 0);

    globalRotation.makeRotate(0, ofVec3f(1, 0, 0), 0, ofVec3f(0, 1, 0), 0, ofVec3f(0, 0, 1));
    localRotation.makeRotate(0, ofVec3f(1, 0, 0), 0, ofVec3f(0, 1, 0), 0, ofVec3f(0, 0, 1));

    globalScale = localScale = ofVec3f(1, 1, 1);
}

ofVec3f Transform::getPosition() const
{
    return localPosition;
}

void Transform::setPosition(float x, float y, float z)
{
    ofVec3f newLocalPosition = ofVec3f(x, y, z);
    ofLog() << localPosition << " -> " << newLocalPosition;
    globalPosition += (newLocalPosition - localPosition);
    localPosition = newLocalPosition;
}

void Transform::translate(float dx, float dy, float dz)
{
    ofVec3f delta = ofVec3f(dx, dy, dz);

    localPosition += delta;
    globalPosition += delta;
}

ofQuaternion Transform::getRotation() const
{
    return localRotation;
}

void Transform::getRotate(float & angle, float & x, float & y, float & z)
{
    localRotation.getRotate(angle, x, y, z);
}

void Transform::setRotation(float x, float y, float z)
{
    ofQuaternion newLocalRotation = ofQuaternion(x, ofVec3f(1, 0, 0), y, ofVec3f(0, 1, 0), z, ofVec3f(0, 0, 1));
    ofQuaternion delta = localRotation.inverse() * newLocalRotation;
    globalRotation *= delta;
    localRotation = newLocalRotation;
}

void Transform::rotate(float degrees, float x, float y, float z)
{
    ofQuaternion rotation = ofQuaternion(degrees, ofVec3f(x, y, z));

    localRotation *= rotation;
    globalRotation *= rotation;
}

ofVec3f Transform::getScale() const
{
    return localScale;
}

void Transform::setScale(float x, float y, float z)
{
    ofVec3f newLocalScale = ofVec3f(x, y, z);
    globalScale *= (newLocalScale / localScale);
    localScale = newLocalScale;
}

void Transform::reScale(float x, float y, float z)
{
    ofVec3f scaleFactors = ofVec3f(x, y, z);

    localScale *= scaleFactors;
    globalScale *= scaleFactors;
}

void Transform::applyToModelViewMatrix()
{
    ofTranslate(localPosition);

    ofScale(localScale);

    float angle, x, y, z;
    localRotation.getRotate(angle, x, y, z);
    ofRotate(angle, x, y, z);
}

void Transform::setRelativeTo(Transform other)
{
    localPosition = globalPosition - other.globalPosition;

    localRotation *= other.globalRotation.inverse() * globalRotation;

    localScale = globalScale / other.globalScale;
}

bool Transform::operator==(const Transform &obj1)
{
    if (localPosition != obj1.localPosition)
        return false;
    if (localRotation != obj1.localRotation)
        return false;
    if (localScale != obj1.localScale)
        return false;
    return true;
}

bool Transform::operator!=(const Transform &obj1)
{
    return !(*this == obj1);
}

void Transform::setGlobal()
{
    localPosition = globalPosition;
    localRotation = globalRotation;
    localScale = globalScale;
}
