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

void GameObject::setRotation(float thetaX, float thetaY, float thetaZ)
{
    transform.setRotation(thetaX, thetaY, thetaZ);
}

GameObject::~GameObject()
{}
