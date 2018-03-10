#pragma once
#include <vector>
#include "gameobject.h"
#include "command.h"

class Scene
{
private:
    vector<GameObject*> gameObjects;
    vector<GameObject*> nonChildrenGameObjects;
    void deleteAllGameObjects();
	CommandHandler history_;
    size_t selectedGameObjectID;
    GameObject* selectedGameObject;

public:
    Scene();
    Scene(const Scene& other);

    void setup();
    void update();
    void draw();

    void addGameObject(GameObject* gameObject);
    void translateSelectedGameObject(float dx, float dy, float dz);
    void rotateSelectedGameObject(float degrees, float x, float y, float z);
    void rescaleSelectedGameObject(float x, float y, float z);
    void setPositionSelectedGameObject(float x, float y, float z);
    void setRotationSelectedGameObject(ofVec3f rotation);
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

    GameObject* getGameObject(size_t index);
    void removeGameObject(GameObject* gameObjectToRemove);
    void removeGameObject(size_t index);
    void removeNonChildGameObject(GameObject * gameObjectToRemove);
    bool isANonChildGameObject(GameObject * gameObjectToFind);

    int getSelectedGameObjectID();
    int getGameObjectID(GameObject* gameObject);
    void setSelectedGameObject(size_t gameObjectID);

    int getSelectedGameObjectParentID();
    void setSelectedGameObjectParent(int parentGameObjectID);

    bool isNewParentIDInSelectedGameObjectChildren(int newParentID);
    bool recursiveIsNewParentIDInSelectedGameObjectChildren(int newParentID, vector<GameObject*>);

    Scene& operator=(const Scene& other);

    ~Scene();
};