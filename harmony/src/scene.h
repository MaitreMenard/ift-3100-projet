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
    void updateSelectedGameObjectColor(ofColor color);
    void updateSelectedGameObjectRotation(ofVec3f rotation);
    void draw();

    void addGameObject(GameObject* gameObject);
    void translateSelectedGameObject(float dx, float dy, float dz);
    void rescaleSelectedGameObject(float x, float y, float z);
    void rotateSelectedGameObject(float degrees, float x, float y, float z);
    void setPositionSelectedGameObject(float x, float y, float z);
    void setScaleSelectedGameObject(float x, float y, float z);

    Scene& operator=(const Scene& other);

    ~Scene();
};