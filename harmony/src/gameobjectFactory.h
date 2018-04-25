#pragma once
#include "ofMain.h"
#include "gameobject.h"
#include "gameobjects/cube.h"
#include "gameobjects/sphere.h"
#include "gameobjects/triangle.h"
#include "gameobjects/rectangle.h"
#include "gameobjects/line.h"
#include "gameobjects/polygone.h"
#include "gameobjects/model3D.h"
#include "gameobjects/arrow.h"
#include "gameobjects/star.h"
#include "gameobjects/mirror.h"
#include "gameobjects/bezier_curve.h"
#include "gameobjects/hermite_curve.h"

class GameObjectFactory
{
public:
    GameObject* createNewGameObject(size_t shapeType, Texture* texture);
private:
    const string cubeText = "Cube";
    const string sphereText = "Sphere";
    const string rectangleText = "Rectangle";
    const string triangleText = "Triangle";
    const string pentagonText = "Pentagon";
    const string circleText = "Circle";
    const string lineText = "Line";
    const string arrowText = "Arrow";
    const string starText = "Star";
    const string portalText = "Portal";
    const string falconText = "Millenium Falcon";
    const string xwingText = "X-Wing";
    const string bezierCurveText = "Bezier Curve";
    const string hermiteCurveText = "Hermite Curve";
};

enum ShapeType
{
    Shape_Sphere,
    Shape_Cube,
    Shape_Line,
    Shape_Triangle,
    Shape_Rectangle,
    Shape_Pentagon,
    Shape_Circle,
    Shape_Arrow,
    Shape_Star,
    Shape_Falcon,
    Shape_XWing,
    Shape_Portal,
    Shape_Bezier,
    Shape_Hermite
};