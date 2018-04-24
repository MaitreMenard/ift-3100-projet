#include "sphere.h"

Sphere::Sphere(std::string name, Texture* texture) : GameObject(name, texture)
{
    //TODO: use texture coordinates
    ofSpherePrimitive spherePrimitive = ofSpherePrimitive();
    spherePrimitive.setRadius(defaultRadius);

    model = spherePrimitive.getMesh();
    nbVertex = model.getVertices().size();

    gameObjectIs2D = false;
}
