#pragma once
#include <vector>
#include "ofMain.h"
#include "transform.h"

class GameObject
{
private:
    void deleteAllChildren();

protected:
    ofTexture texture;
    Transform transform;
    std::vector<GameObject*> children;
    ofMesh model;
    GameObject* parentGameObject;

    int nbVertex;

public:
    GameObject();
    GameObject(const GameObject& other);

    virtual void setup();
    virtual void update();
    virtual void draw();

    void drawDelimitationBox();

    ofVec3f getPosition();
    void setPosition(float x, float y, float z);
    void translate(float dx, float dy, float dz);

    ofQuaternion getRotation();
    void setRotation(float x, float y, float z);
    void rotate(float degrees, float x, float y, float z);

    ofVec3f getScale();
    void setScale(float x, float y, float z);
    void reScale(float x, float y, float z);

    ofColor getColor();
    void setColor(ofColor color);

    void addChild(GameObject* child);
    GameObject* getChild(size_t index);
    void removeChild(size_t index);
    void removeChild(GameObject* childToRemove);
    bool hasChildren();
    vector<GameObject *> getChildren();

    GameObject* getParentGameObject();
    void setParentGameObject(GameObject* parent);

    GameObject& operator=(const GameObject& other);

    void setTexture(ofPixels * pixels);

    virtual ~GameObject();
};