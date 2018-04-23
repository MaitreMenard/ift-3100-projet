#pragma once
#include <vector>
#include "gameobject.h"
#include "command.h"

class Scene
{
private:
    const string exceptionChildParent = "You cannot set the parent of an object to one of its children.";
    const string exceptionParentItself = "You cannot set the parent of an object to itself.";

    vector<GameObject*> gameObjects;
    vector<GameObject*> nonChildrenGameObjects;
    CommandHandler history_;
    GameObject* selectedGameObject;

    void deleteAllGameObjects();
    void removeSelectedGameObjectFromItsParentChildren();

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
    void setPositionSelectedGameObject(ofVec3f position);
    void setRotationSelectedGameObject(ofVec3f rotation);
    void setScaleSelectedGameObject(ofVec3f scale);

    void undo();
    void redo();
    void enableUndoRedo() { history_.enable(); };
    void disableUndoRedo() { history_.disable(); };
    void setColorSelectedGameObject(ofColor color);

    ofVec3f getPositionSelectedGameObject();
    ofVec3f getEulerRotationSelectedGameObject();
    ofVec3f getScaleSelectedGameObject();
    ofColor getColorSelectedGameObject();

    GameObject* getGameObject(size_t index);    //TODO: rename ByIndex
    size_t getNumberOfGameObjects();
    void removeGameObject(GameObject* gameObjectToRemove);
    void removeGameObject(size_t index);
    void removeNonChildGameObject(GameObject * gameObjectToRemove);
    bool isANonChildGameObject(GameObject * gameObjectToFind);

    bool isSelectedGameObject2D();

    GameObject* getSelectedGameObject();
    size_t getGameObjectID(GameObject* gameObject);
    void setSelectedGameObject(GameObject* gameObject);
    Texture* getSelectedGameObjectTexture();
    void setSelectedGameObjectTexture(Texture* texture);

    size_t getSelectedGameObjectParentID();
    void setSelectedGameObjectParent(GameObject* parentGameObject);
    void removeSelectedGameObjectParent();

    bool isNewParentInSelectedGameObjectChildren(GameObject* newParent);    //TODO: make private
    bool recursiveIsNewParentInSelectedGameObjectChildren(GameObject* newParent, vector<GameObject*>);  //TODO: make private

    Scene& operator=(const Scene& other);

    ~Scene();
};
