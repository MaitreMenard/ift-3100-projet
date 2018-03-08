#pragma once
#include "ofMain.h"
#include "transform.h"

class GameObject
{
protected:
    Transform transform;
    ofMesh model;

    int nbVertex;

public:
    virtual void setup();
    virtual void update();
    virtual void draw();

    void translate(float dx, float dy, float dz);
    void reScale(float x, float y, float z);
    void rotate(float degrees, float x, float y, float z);
    void setPosition(float x, float y, float z);
    ofQuaternion getRotation();
    void setRotation(float x, float y, float z);
    void setScale(float x, float y, float z);

    ofColor getColor();
    void setColor(ofColor color);

    virtual ~GameObject();
};