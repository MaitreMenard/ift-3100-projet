#include "scene.h"

Scene::Scene()
{
    selectedGameObject = nullptr;
}

Scene::Scene(const Scene& other)
{
    for (GameObject* gameObject : other.gameObjects)
    {
        gameObjects.push_back(gameObject);
    }

    selectedGameObject = other.selectedGameObject;
}

void Scene::setup()
{
    for (GameObject* gameObject : gameObjects)
    {
        gameObject->setup();
    }
}

void Scene::update()
{
    for (GameObject* gameObject : gameObjects)
    {
        gameObject->update();
    }
}

void Scene::setSelectedGameObject(size_t gameObjectID) {
    selectedGameObjectID = gameObjectID;
    selectedGameObject = gameObjects[gameObjectID];
}

int Scene::getSelectedGameObjectID() {
    return selectedGameObjectID;
}

ofVec3f Scene::getEulerRotationSelectedGameObject() {
    return selectedGameObject->getRotation().getEuler();
}

void Scene::updateSelectedGameObjectRotation(ofVec3f rotation)
{
    if (selectedGameObject != nullptr && selectedGameObject->getRotation().getEuler() != rotation)
    {
        selectedGameObject->setRotation(rotation.x, rotation.y, rotation.z);
    }
}

void Scene::setColorSelectedGameObject(ofColor color)
{
    selectedGameObject->setColor(color);
	history_.add(new Command(selectedGameObject));
}

ofVec3f Scene::getPositionSelectedGameObject() {
    return selectedGameObject->getPosition();
}

ofVec3f Scene::getScaleSelectedGameObject() {
    return selectedGameObject->getScale();
}

ofColor Scene::getColorSelectedGameObject() {
    return selectedGameObject->getColor();
}

void Scene::draw()
{
    for (GameObject* gameObject : gameObjects)
    {
        if (gameObject->getParentGameObjectID() == 0) {
            gameObject->draw();
        }
    }

    if (selectedGameObject != nullptr)
    {
        selectedGameObject->drawDelimitationBox();
    }
}

void Scene::addGameObject(GameObject* gameObject)
{
    gameObjects.push_back(gameObject);
}

GameObject * Scene::getGameObject(size_t index)
{
    return gameObjects.at(index);
}

void Scene::removeGameObject(GameObject * gameObjectToRemove)
{
    gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), gameObjectToRemove), gameObjects.end());
}

void Scene::removeNonChildGameObject(GameObject * gameObjectToRemove)
{
    nonChildrenGameObjects.erase(std::remove(nonChildrenGameObjects.begin(), nonChildrenGameObjects.end(), gameObjectToRemove), nonChildrenGameObjects.end());
}

bool Scene::isANonChildGameObject(GameObject * gameObjectToFind)
{
    return std::find(nonChildrenGameObjects.begin(), nonChildrenGameObjects.end(), gameObjectToFind) != nonChildrenGameObjects.end();
}

void Scene::removeGameObject(size_t index)
{
    std::vector<GameObject*>::iterator it = gameObjects.begin();
    std::advance(it, index);
    gameObjects.erase(it);
}

void Scene::translateSelectedGameObject(float dx, float dy, float dz)
{
    selectedGameObject->translate(dx, dy, dz);
}

void Scene::setPositionSelectedGameObject(float x, float y, float z)
{
    selectedGameObject->setPosition(x, y, z);
	history_.add(new Command(selectedGameObject));
}

void Scene::setScaleSelectedGameObject(float x, float y, float z)
{
    selectedGameObject->setScale(x, y, z);
	history_.add(new Command(selectedGameObject));
}

void Scene::rescaleSelectedGameObject(float x, float y, float z)
{
    selectedGameObject->reScale(x, y, z);
	history_.add(new Command(selectedGameObject));
}

void Scene::rotateSelectedGameObject(float degrees, float x, float y, float z)
{
    selectedGameObject->rotate(degrees, x, y, z);
}

int Scene::getSelectedGameObjectParentID() {
    return selectedGameObject->getParentGameObjectID();
}

void Scene::setSelectedGameObjectParent(int parentGameObjectID) {
    //TODO: Make sure transform is modified when setting a new parent or having no parents
    if (selectedGameObject->getParentGameObjectID() > 0) {
        getGameObject(selectedGameObject->getParentGameObjectID() - 1)->removeChild(selectedGameObject);
    }
    if (parentGameObjectID > 0) {
        selectedGameObject->setParentGameObjectID(parentGameObjectID);
        getGameObject(parentGameObjectID - 1)->addChild(selectedGameObject);
        removeNonChildGameObject(selectedGameObject);
    }
    else if(!isANonChildGameObject(selectedGameObject)){
        nonChildrenGameObjects.push_back(selectedGameObject);
    }
}

bool Scene::isNewParentIDInSelectedGameObjectChildren(int newParentID) {
    return recursiveIsNewParentIDInSelectedGameObjectChildren(newParentID, selectedGameObject->getChildren());
}

bool Scene::recursiveIsNewParentIDInSelectedGameObjectChildren(int newParentID, vector<GameObject*> children) {
    bool cannotBeItsNewParent = false;
    for (GameObject* child : children) {
        if (getGameObjectID(child) + 1 == newParentID || recursiveIsNewParentIDInSelectedGameObjectChildren(newParentID, child->getChildren())) {
            cannotBeItsNewParent = true;
            break;
        }
    }
    return cannotBeItsNewParent;
}

int Scene::getGameObjectID(GameObject* gameObject) {
    return find(gameObjects.begin(), gameObjects.end(), gameObject) - gameObjects.begin();
}

Scene& Scene::operator=(const Scene& other)
{
    deleteAllGameObjects();
    gameObjects.assign(other.gameObjects.begin(), other.gameObjects.end());
    selectedGameObject = other.selectedGameObject;
    return *this;
}

void Scene::deleteAllGameObjects()
{
    for (GameObject* gameObject : nonChildrenGameObjects)
    {
        delete gameObject;
    }
}

void Scene::undo() {
	history_.undo();
}

void Scene::redo(){
	history_.redo();
}

Scene::~Scene()
{
    deleteAllGameObjects();
    nonChildrenGameObjects.clear();
    gameObjects.clear();
}
