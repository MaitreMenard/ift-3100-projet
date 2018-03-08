#pragma once
#include <vector>
#include "gameobject.h"

class Scene
{
private:
    std::vector<GameObject*> gameObjects;
    void deleteAllGameObjects();

public:
    Scene();
    Scene(const Scene& other);

    void setup();
    void update();
    void updateSelectedGameObjectRotation(ofVec3f rotation);
    void draw();

    void addGameObject(GameObject* gameObject);
    void translateSelectedGameObject(float dx, float dy, float dz);
    void rescaleSelectedGameObject(float x, float y, float z);
    void rotateSelectedGameObject(float degrees, float x, float y, float z);
    void setPositionSelectedGameObject(float x, float y, float z);
    void setScaleSelectedGameObject(float x, float y, float z);
    void setColorSelectedGameObject(ofColor color);

    ofVec3f getPositionSelectedGameObject();
    ofVec3f getEulerRotationSelectedGameObject();
    ofVec3f getScaleSelectedGameObject();
    ofColor getColorSelectedGameObject();

    Scene& operator=(const Scene& other);

    ~Scene();
};