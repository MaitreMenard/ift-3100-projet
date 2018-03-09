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
    void updateSelectedGameObjectRotation(int selectedGameObjectID, ofVec3f rotation);
    void draw();

    void addGameObject(GameObject* gameObject);
    void translateSelectedGameObject(int selectedGameObjectID, float dx, float dy, float dz);
    void rescaleSelectedGameObject(int selectedGameObjectID, float x, float y, float z);
    void rotateSelectedGameObject(int selectedGameObjectID, float degrees, float x, float y, float z);
    void setPositionSelectedGameObject(int selectedGameObjectID, float x, float y, float z);
    void setScaleSelectedGameObject(int selectedGameObjectID, float x, float y, float z);
    void setColorSelectedGameObject(int selectedGameObjectID, ofColor color);

    ofVec3f getPositionSelectedGameObject(int selectedGameObjectID);
    ofVec3f getEulerRotationSelectedGameObject(int selectedGameObjectID);
    ofVec3f getScaleSelectedGameObject(int selectedGameObjectID);
    ofColor getColorSelectedGameObject(int selectedGameObjectID);

    Scene& operator=(const Scene& other);

    ~Scene();
};