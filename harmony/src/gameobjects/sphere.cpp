#include "sphere.h"

Sphere::Sphere()
{
    ofSpherePrimitive spherePrimitive = ofSpherePrimitive();
    spherePrimitive.setRadius(defaultRadius);

    model = spherePrimitive.getMesh();
    nbVertex = model.getVertices().size();
}
