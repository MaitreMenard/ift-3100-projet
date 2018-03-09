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

ofVec3f Scene::getEulerRotationSelectedGameObject() {
    if (gameObjects.size() > 0)
    {
        return gameObjects[0]->getRotation().getEuler();
    }
    return ofVec3f(0, 0, 0);
}

void Scene::updateSelectedGameObjectRotation(ofVec3f rotation)
{
    //TODO: Actually use the selected object in the scene, not the first
    if (gameObjects.size() > 0 && gameObjects[0]->getRotation().getEuler() != rotation)
    {
        gameObjects[0]->setRotation(rotation.x, rotation.y, rotation.z);
    }
}

void Scene::setColorSelectedGameObject(ofColor color)
{
    //TODO: Actually use the selected object in the scene, not the first
    if (gameObjects.size() > 0 && gameObjects[0]->getColor() != color)
    {
        gameObjects[0]->setColor(color);
    }
}

ofVec3f Scene::getPositionSelectedGameObject(int selectedGameObjectID) {
    if (gameObjects.size() > 0)
    {
        return gameObjects[selectedGameObjectID]->getPosition();
    }
    return ofVec3f(0, 0, 0);
}

ofVec3f Scene::getScaleSelectedGameObject() {
    if (gameObjects.size() > 0)
    {
        return gameObjects[0]->getScale();
    }
    return ofVec3f(1, 1, 1);
}

ofColor Scene::getColorSelectedGameObject() {
    if (gameObjects.size() > 0)
    {
        return gameObjects[0]->getColor();
    }
    return ofColor(255, 255, 255);
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

void Scene::translateSelectedGameObject(float dx, float dy, float dz)
{
    //TODO: modify this when gameObject selection will be implemented
    if (gameObjects.size() > 0)
    {
        gameObjects[0]->translate(dx, dy, dz);
    }
}

void Scene::setPositionSelectedGameObject(float x, float y, float z)
{
    if (gameObjects.size() > 0)
    {
        gameObjects[0]->setPosition(x, y, z);
    }
}

void Scene::setScaleSelectedGameObject(float x, float y, float z)
{
    if (gameObjects.size() > 0)
    {
        gameObjects[0]->setScale(x, y, z);
    }
}

void Scene::rescaleSelectedGameObject(float x, float y, float z)
{
    if (gameObjects.size() > 0)
    {
        gameObjects[0]->reScale(x, y, z);
    }
}

void Scene::rotateSelectedGameObject(float degrees, float x, float y, float z)
{
    //TODO: modify this when gameObject selection will be implemented
    if (gameObjects.size() > 0)
    {
        gameObjects[0]->rotate(degrees, x, y, z);
    }
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
