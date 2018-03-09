#pragma once
#include <vector>
#include "gameobject.h"
#include "command.h"

class Scene
{
private:
    std::vector<GameObject*> gameObjects;
    void deleteAllGameObjects();
	CommandHandler history_;

public:
    Scene();
    Scene(const Scene& other);

    void setup();
    void update();
    void updateSelectedGameObjectRotation(ofVec3f rotation);
    void draw();

    void addGameObject(GameObject* gameObject);
    GameObject* getGameObject(size_t index);
    void removeGameObject(GameObject* gameObjectToRemove);
    void removeGameObject(size_t index);

    void translateSelectedGameObject(float dx, float dy, float dz);
    void rescaleSelectedGameObject(float x, float y, float z);
    void rotateSelectedGameObject(float degrees, float x, float y, float z);
    void setPositionSelectedGameObject(float x, float y, float z);
    void setScaleSelectedGameObject(float x, float y, float z);

	void undo();
	void redo();
	void enableUndoRedo() { history_.enable(); };
	void disableUndoRedo() { history_.disable(); };
    void setColorSelectedGameObject(ofColor color);

    ofVec3f getPositionSelectedGameObject();
    ofVec3f getEulerRotationSelectedGameObject();
    ofVec3f getScaleSelectedGameObject();
    ofColor getColorSelectedGameObject();

    Scene& operator=(const Scene& other);

    ~Scene();
};