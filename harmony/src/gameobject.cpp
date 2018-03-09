#include "gameobject.h"

GameObject::GameObject()
{}

GameObject::GameObject(const GameObject & other)
{
    for (GameObject* child : other.children)
    {
        children.push_back(child);
    }
}

void GameObject::setup()
{

}

void GameObject::update()
{

}

void GameObject::draw()
{
    ofPushMatrix();

    transform.applyToModelViewMatrix();

    model.draw();
    for (GameObject* child : children)
    {
        child->draw();
    }

    ofPopMatrix();
}

void GameObject::drawDelimitationBox()
{
    ofPushMatrix();

    transform.applyToModelViewMatrix();

    ofBoxPrimitive delimitationBox = ofBoxPrimitive();
    delimitationBox.setSideColor(delimitationBox.SIDE_FRONT, ofColor(0, 255, 0));
    delimitationBox.setSideColor(delimitationBox.SIDE_BACK, ofColor(0, 255, 0));
    delimitationBox.setSideColor(delimitationBox.SIDE_LEFT, ofColor(0, 255, 0));
    delimitationBox.setSideColor(delimitationBox.SIDE_RIGHT, ofColor(0, 255, 0));
    delimitationBox.setSideColor(delimitationBox.SIDE_TOP, ofColor(0, 255, 0));
    delimitationBox.setSideColor(delimitationBox.SIDE_BOTTOM, ofColor(0, 255, 0));
    /*for (int i = delimitationBox.S; i < 6; i++)
    {
        delimitationBox.setSideColor(i, ofColor(0, 255, 0));
    }*/

    ofVec3f scale = transform.getScale();
    delimitationBox.setWidth(scale.x);
    delimitationBox.setHeight(scale.y);
    delimitationBox.setDepth(scale.z);

    //delimitationBox.drawWireframe();
    delimitationBox.drawFaces();

    ofPopMatrix();
}

ofVec3f GameObject::getPosition()
{
    return transform.getPosition();
}

void GameObject::translate(float dx, float dy, float dz)
{
    transform.translate(dx, dy, dz);
}

void GameObject::setPosition(float x, float y, float z)
{
    transform.setPosition(x, y, z);
}

ofQuaternion GameObject::getRotation()
{
    return transform.getRotation();
}

void GameObject::rotate(float degrees, float x, float y, float z)
{
    transform.rotate(degrees, x, y, z);
}

void GameObject::setRotation(float x, float y, float z)
{
    transform.setRotation(x, y, z);
}

ofVec3f GameObject::getScale()
{
    return transform.getScale();
}

void GameObject::reScale(float x, float y, float z)
{
    transform.reScale(x, y, z);
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

void GameObject::addChild(GameObject * child)
{
    children.push_back(child);
}

GameObject * GameObject::getChild(size_t index)
{
    return children.at(index);
}

void GameObject::removeChild(size_t index)
{
    std::vector<GameObject*>::iterator it = children.begin();
    std::advance(it, index);
    children.erase(it);

}

GameObject & GameObject::operator=(const GameObject & other)
{
    deleteAllChildren();
    children.assign(other.children.begin(), other.children.end());
    return *this;
}

void GameObject::deleteAllChildren()
{
    for (GameObject* child : children)
    {
        delete child;
    }
}

GameObject::~GameObject()
{
    deleteAllChildren();
    children.clear();
}
