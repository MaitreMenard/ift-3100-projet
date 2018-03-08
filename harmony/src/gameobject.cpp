#include "gameobject.h"

void GameObject::setup()
{

}

void GameObject::update()
{

}

void GameObject::draw()
{

}

void GameObject::translate(float dx, float dy, float dz)
{
    transform.translate(dx, dy, dz);
}

void GameObject::reScale(float x, float y, float z)
{
    transform.reScale(x, y, z);
}

void GameObject::rotate(float degrees, float x, float y, float z)
{
    transform.rotate(degrees, x, y, z);
}

void GameObject::setPosition(float x, float y, float z)
{
    transform.setPosition(x, y, z);
}

ofQuaternion GameObject::getRotation() {
    return transform.getRotation();
}

void GameObject::setRotation(float x, float y, float z)
{
    transform.setRotation(x, y, z);
}

void GameObject::setScale(float x, float y, float z)
{
    transform.setScale(x, y, z);
}

ofColor GameObject::getColor() {
    if (model.getColors().empty()) {
        return ofColor(0, 0, 0);
    }
    return model.getColor(0);
}

void GameObject::setColor(ofColor color) {
    model.clearColors();
    for (int i = 0; i < nbVertex; i++) {
        model.addColor(color);
    }
}

GameObject::~GameObject()
{}
