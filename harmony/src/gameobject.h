#pragma once
#include <vector>
#include "ofMain.h"
#include "transform.h"

class GameObject
{
private:
    void deleteAllChildren();

protected:
    Transform transform;
    std::vector<GameObject*> children;
    ofMesh model;

    int nbVertex;

public:
    GameObject();
    GameObject(const GameObject& other);

    virtual void setup();
    virtual void update();
    virtual void draw();

    void translate(float dx, float dy, float dz);
    void reScale(float x, float y, float z);
    void rotate(float degrees, float x, float y, float z);
    void setPosition(float x, float y, float z);
    void setRotation(float thetaX, float thetaY, float thetaZ);
    void setScale(float x, float y, float z);

    ofColor getColor();
    void setColor(ofColor color);

    void addChild(GameObject* child);
    GameObject* getChild(size_t index);
    void removeChild(size_t index);

    GameObject& operator=(const GameObject& other);

    virtual ~GameObject();
};