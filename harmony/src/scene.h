#pragma once
#include <vector>
#include "gameobject.h"

class Scene
{
private:
    vector<GameObject*> gameObjects;
    void deleteAllGameObjects();
    size_t selectedGameObjectID;
    GameObject* selectedGameObject;

public:
    Scene();
    Scene(const Scene& other);

    void setup();
    void update();
    void updateSelectedGameObjectRotation(ofVec3f rotation);
    void draw();

    void setSelectedGameObject(size_t gameObjectID);
    int getSelectedGameObjectID();

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

    GameObject* getGameObject(size_t index);
    void removeGameObject(size_t index);

    int getSelectedGameObjectParentID();
    void setSelectedGameObjectParent(int parentGameObjectID);

    Scene& operator=(const Scene& other);

    ~Scene();
};