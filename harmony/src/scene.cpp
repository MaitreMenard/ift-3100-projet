#include "scene.h"

Scene::Scene()
{}

Scene::Scene(const Scene& other)
{
    for (GameObject* gameObject : other.gameObjects)
    {
        gameObjects.push_back(gameObject);
    }
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
        gameObject->draw();
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
}

void Scene::setScaleSelectedGameObject(float x, float y, float z)
{
    selectedGameObject->setScale(x, y, z);
}

void Scene::rescaleSelectedGameObject(float x, float y, float z)
{
    selectedGameObject->reScale(x, y, z);
}

void Scene::rotateSelectedGameObject(float degrees, float x, float y, float z)
{
    selectedGameObject->rotate(degrees, x, y, z);
}

int Scene::getSelectedGameObjectParentID() {
    return selectedGameObject->getParentGameObjectID();
}

void Scene::setSelectedGameObjectParentID(int parentGameObjectID) {
    selectedGameObject->setParentGameObjectID(parentGameObjectID);
}

Scene& Scene::operator=(const Scene& other)
{
    deleteAllGameObjects();
    gameObjects.assign(other.gameObjects.begin(), other.gameObjects.end());
    return *this;
}

void Scene::deleteAllGameObjects()
{
    for (GameObject* gameObject : gameObjects)
    {
        delete gameObject;
    }
}

Scene::~Scene()
{
    deleteAllGameObjects();
    gameObjects.clear();
}
