#include "gameobjectFactory.h"

GameObject* GameObjectFactory::createNewGameObject(size_t shapeType, Texture* texture) {
    if (shapeType == Shape_Sphere)
    {
        return new Sphere(sphereText, texture);
    }
    else if (shapeType == Shape_Cube)
    {
        return new Cube(cubeText, texture);
    }
    else if (shapeType == Shape_Line)
    {
        return new Line(lineText);
    }
    else if (shapeType == Shape_Triangle)
    {
        return new Triangle(triangleText, texture);
    }
    else if (shapeType == Shape_Rectangle)
    {
        return new Rektangle(rectangleText, texture);
    }
    else if (shapeType == Shape_Pentagon)
    {
        return new Polygone(pentagonText, texture, 5);
    }
    else if (shapeType == Shape_Circle)
    {
        return new Polygone(circleText, texture, 90);
    }
    else if (shapeType == Shape_Arrow)
    {
        return new Arrow(arrowText, texture);
    }
    else if (shapeType == Shape_Star)
    {
        return new Star(starText, texture);
    }
    else if (shapeType == Shape_Portal)
    {
        return new Mirror(portalText, texture);
    }
    else if (shapeType == Shape_Falcon)
    {
        return new Model3D(falconText, "/models/millenium-falcon/millenium-falcon.obj",
            ofVec3f(-0.59, 0.17, 19.0),
            180,
            ofVec3f(0, 0, 1),
            ofVec3f(0.01, 0.01, 0.01));
    }
    else if (shapeType == Shape_XWing)
    {
        return new Model3D(xwingText, "/models/xwing/x-wing.obj",
            ofVec3f(-14.59, 0.17, 19.0),
            180, ofVec3f(0, 0, 1),
            ofVec3f(0.01, 0.01, 0.01));
    }
    else if (shapeType == Shape_Bezier)
    {
        return new BezierCurve(bezierCurveText);
    }
    else if (shapeType == Shape_Hermite)
    {
        return new HermiteCurve(hermiteCurveText);
    }
    else if (shapeType == Shape_PlaneRelief)
    {
        return new PlaneRelief(planeReliefText);
    }
    return nullptr;
}
