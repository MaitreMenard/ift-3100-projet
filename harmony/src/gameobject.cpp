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

    ofTranslate(transform.getPosition());

    ofScale(transform.getScale().x, transform.getScale().y, transform.getScale().z);

    float angle, x, y, z;
    transform.getRotate(angle, x, y, z);
    ofRotate(angle, x, y, z);

    model.draw();
    for (GameObject* child : children)
    {
        child->draw();
    }

    ofPopMatrix();
}

ofVec3f GameObject::getPosition()
{
    return transform.getPosition();
}

void GameObject::setPosition(float x, float y, float z)
{
    transform.setPosition(x, y, z);
}

void GameObject::translate(float dx, float dy, float dz)
{
    transform.translate(dx, dy, dz);
}

ofQuaternion GameObject::getRotation()
{
    return transform.getRotation();
}

void GameObject::setRotation(float x, float y, float z)
{
    transform.setRotation(x, y, z);
}

void GameObject::rotate(float degrees, float x, float y, float z)
{
    transform.rotate(degrees, x, y, z);
}

ofVec3f GameObject::getScale()
{
    return transform.getScale();
}

void GameObject::setScale(float x, float y, float z)
{
    transform.setScale(x, y, z);
}

void GameObject::reScale(float x, float y, float z)
{
    transform.reScale(x, y, z);
}

ofColor GameObject::getColor() {
    if (model.getColors().empty()) {
        return ofColor(255, 255, 255);
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

int GameObject::getParentGameObjectID() {
    return parentGameObjectID;
}

void GameObject::setParentGameObjectID(int parentGameObjectID) {
    this->parentGameObjectID = parentGameObjectID;
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

void GameObject::setTexture(ofPixels * pixels) {
    texture.clear();
    texture.allocate(*pixels);
    texture.setTextureWrap(GL_REPEAT, GL_REPEAT);
}

GameObject::~GameObject()
{
    deleteAllChildren();
    children.clear();
}
