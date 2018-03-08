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
	gameObjects[0]->setPosition(x, y, z);
}

void Scene::setScaleSelectedGameObject(float x, float y, float z)
{
	gameObjects[0]->setScale(x, y, z);
}

void Scene::rescaleSelectedGameObject(float x, float y, float z)
{
    gameObjects[0]->reScale(x, y, z);
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
