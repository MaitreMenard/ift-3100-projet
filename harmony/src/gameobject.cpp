#include "gameobject.h"

GameObject::GameObject(std::string name, Texture* texture)
{
    this->name = name;
    this->texture = texture;

    parentGameObject = nullptr;

    boundingBox = ofBoxPrimitive();
    boundingBox.set(1);

    isSelected = false;
}

GameObject::GameObject(const GameObject & other)
{
    name = other.name;
    texture = other.texture;
    transform = other.transform;
    model = other.model;
    parentGameObject = other.parentGameObject;
    boundingBox = other.boundingBox;
    nbVertex = other.nbVertex;
    isSelected = other.isSelected;

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

    texture->bind();
    model.draw();
    texture->unbind();

    for (GameObject* child : children)
    {
        child->draw();
    }

    if (isSelected)
    {
        drawBoundingBox();
    }

    ofPopMatrix();
}

std::string GameObject::getName()
{
    return name;
}

void GameObject::drawBoundingBox()
{
    for (size_t i = 0; i < 6; i++)
    {
        boundingBox.setSideColor(i, ofColor(0, 255, 0));
    }

    boundingBox.drawWireframe();
}

ofVec3f GameObject::getPosition()
{
    return transform.getPosition();
}

void GameObject::setPosition(ofVec3f position)
{
    transform.setPosition(position);
}

void GameObject::translate(float dx, float dy, float dz)
{
    transform.translate(dx, dy, dz);
}

ofQuaternion GameObject::getRotation()
{
    return transform.getRotation();
}

ofVec3f GameObject::getEulerAngles()
{
    return transform.getRotation().getEuler();
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

void GameObject::setScale(ofVec3f scale)
{
    transform.setScale(scale);
}

void GameObject::reScale(float x, float y, float z)
{
    transform.reScale(x, y, z);
}

ofColor GameObject::getColor()
{
    if (model.getColors().empty())
    {
        return ofColor(255, 255, 255);
    }
    return model.getColor(0);
}

void GameObject::setColor(ofColor color)
{
    model.clearColors();
    for (size_t i = 0; i < nbVertex; i++)
    {
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

void GameObject::setChildren(vector<GameObject *> child)
{
    children.clear();
    for (vector<GameObject*>::iterator it = child.begin(); it != child.end(); ++it)
        children.push_back(*it);
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

GameObject* GameObject::getParentGameObject()
{
    return parentGameObject;
}

void GameObject::setParentGameObject(GameObject* parentGameObject)
{
    this->parentGameObject = parentGameObject;
}

void GameObject::setSelected(bool isSelected)
{
    this->isSelected = isSelected;
}

bool GameObject::hasChildren()
{
    return children.size() > 0;
}

GameObject & GameObject::operator=(const GameObject & other)
{
    deleteAllChildren();
    children.assign(other.children.begin(), other.children.end());

    name = other.name;
    texture = other.texture;
    transform = other.transform;
    model = other.model;
    parentGameObject = other.parentGameObject;
    boundingBox = other.boundingBox;
    nbVertex = other.nbVertex;
    isSelected = other.isSelected;

    return *this;
}

void GameObject::deleteAllChildren()
{
    for (GameObject* child : children)
    {
        delete child;
    }
}

void GameObject::setTexture(Texture* texture)
{
    this->texture = texture;
}

Texture* GameObject::getTexture()
{
    return texture;
}

bool GameObject::is2D() 
{
    return gameObjectIs2D;
}

GameObject::~GameObject()
{
    deleteAllChildren();
    children.clear();
}
