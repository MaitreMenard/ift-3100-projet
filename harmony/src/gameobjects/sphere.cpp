#include "sphere.h"

Sphere::Sphere(std::string name, Texture* texture) : GameObject(name, texture)
{
    //TODO: use texture coordinates
    ofSpherePrimitive spherePrimitive = ofSpherePrimitive();
    spherePrimitive.setRadius(defaultRadius);
    spherePrimitive.setResolution(100);

    model = spherePrimitive.getMesh();
    nbVertex = model.getVertices().size();

    _hasMaterial = true;
}