#include "sphere.h"

Sphere::Sphere(std::string name, Texture* texture) : GameObject(name, texture)
{
    //TODO: use texture coordinates
    ofSpherePrimitive spherePrimitive = ofSpherePrimitive();
    spherePrimitive.setRadius(defaultRadius);
    spherePrimitive.setResolution(100);

    model = spherePrimitive.getMesh();
    nbVertex = model.getVertices().size();

    hasMaterial = true;

    /*setMaterialDiffuseColor(ofColor(20, 244, 3));
    setMaterialShininess(100);
    setMaterialAmbientColor(ofColor(20, 3, 244));
    setMaterialSpecularColor(ofColor(255, 140, 0));*/
}