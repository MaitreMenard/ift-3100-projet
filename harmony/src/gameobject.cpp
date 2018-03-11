#include "gameobject.h"

GameObject::GameObject()
{
    parentGameObject = nullptr;
}

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

    ofBoxPrimitive delimitationBox = ofBoxPrimitive();
    delimitationBox.set(1);

    for (size_t i = 0; i < 6; i++)
    {
        delimitationBox.setSideColor(i, ofColor(0, 255, 0));
    }

    transform.applyToModelViewMatrix();

    delimitationBox.drawWireframe();

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
    for (size_t i = 0; i < nbVertex; i++) {
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

vector<GameObject *> GameObject::getChildren()
{
    return children;
}

void GameObject::removeChild(size_t index)
{
    std::vector<GameObject*>::iterator it = children.begin();
    std::advance(it, index);
    children.erase(it);
}

void GameObject::removeChild(GameObject * childToRemove)
{
    children.erase(std::remove(children.begin(), children.end(), childToRemove), children.end());
}

GameObject* GameObject::getParentGameObject() {
    return parentGameObject;
}

void GameObject::setParentGameObject(GameObject* parentGameObject) {
    this->parentGameObject = parentGameObject;
    if (parentGameObject != nullptr) {
        transform.setRelativeTo(parentGameObject->transform);
    }
    else {
        transform.setRelativeTo(Transform());
    }
}

bool GameObject::hasChildren() {
    return children.size() > 0;
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
