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

void Scene::setSelectedGameObject(GameObject* gameObject)
{
    if (selectedGameObject != nullptr)
    {
        selectedGameObject->setSelected(false);
    }
    if (gameObject != nullptr)
    {
        selectedGameObject = gameObject;
        selectedGameObject->setSelected(true);
    }
}

GameObject* Scene::getSelectedGameObject()
{
    return selectedGameObject;
}

void Scene::setRotationSelectedGameObject(ofVec3f rotation)
{
    if (selectedGameObject != nullptr && selectedGameObject->getEulerAngles() != rotation)
    {
        selectedGameObject->setRotation(rotation.x, rotation.y, rotation.z);
        history_.add(new Command(selectedGameObject));
    }
}

void Scene::setColorSelectedGameObject(ofColor color)
{
    selectedGameObject->setColor(color);
    history_.add(new Command(selectedGameObject));
}

void Scene::draw()
{
    for (GameObject* gameObject : gameObjects)
    {
        if (gameObject->getParentGameObject() == nullptr)
        {
            gameObject->draw();
        }
    }
}

void Scene::addGameObject(GameObject* gameObject)
{
    gameObjects.push_back(gameObject);
    history_.add(new Command(gameObject));
}

GameObject * Scene::getGameObjectByIndex(size_t index)
{
    return gameObjects.at(index);
}

size_t Scene::getNumberOfGameObjects()
{
    return gameObjects.size();
}

void Scene::removeGameObject(GameObject * gameObjectToRemove)
{
    history_.add(new Command(gameObjectToRemove));
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
    history_.add(new Command(selectedGameObject));
}

void Scene::setPositionSelectedGameObject(ofVec3f position)
{
    selectedGameObject->setPosition(position);
    history_.add(new Command(selectedGameObject));
}

void Scene::setScaleSelectedGameObject(ofVec3f scale)
{
    selectedGameObject->setScale(scale);
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
    history_.add(new Command(selectedGameObject));
}

size_t Scene::getSelectedGameObjectParentID()
{
    if (selectedGameObject->getParentGameObject() != nullptr)
    {
        return getGameObjectID(selectedGameObject->getParentGameObject()) + 1;
    }
    return 0;
}

void Scene::setSelectedGameObjectParent(GameObject* parentGameObject)
{
    if (parentGameObject == selectedGameObject)
    {
        ofLog() << exceptionParentItself;
    }
    else if (isNewParentInSelectedGameObjectChildren(parentGameObject))
    {
        ofLog() << exceptionChildParent;
    }
    else
    {
        removeSelectedGameObjectFromItsParentChildren();

        selectedGameObject->setParentGameObject(parentGameObject);
        parentGameObject->addChild(selectedGameObject);
        removeNonChildGameObject(selectedGameObject);
    }
}

bool Scene::isNewParentInSelectedGameObjectChildren(GameObject* newParent)
{
    return recursiveIsNewParentInSelectedGameObjectChildren(newParent, selectedGameObject->getChildren());
}

bool Scene::recursiveIsNewParentInSelectedGameObjectChildren(GameObject* newParent, vector<GameObject*> children)
{
    bool cannotBeItsNewParent = false;
    for (GameObject* child : children)
    {
        if (newParent == child || recursiveIsNewParentInSelectedGameObjectChildren(newParent, child->getChildren()))
        {
            cannotBeItsNewParent = true;
            break;
        }
    }
    return cannotBeItsNewParent;
}

void Scene::removeSelectedGameObjectFromItsParentChildren()
{
    ofLog() << "Modifying parent hierarchy";
    if (selectedGameObject->getParentGameObject() != nullptr)
    {
        selectedGameObject->getParentGameObject()->removeChild(selectedGameObject);
    }
}

void Scene::removeSelectedGameObjectParent()
{
    removeSelectedGameObjectFromItsParentChildren();

    if (!isANonChildGameObject(selectedGameObject)) //TODO: is this really necessary?
    {
        selectedGameObject->setParentGameObject(nullptr);
        nonChildrenGameObjects.push_back(selectedGameObject);
    }
}

size_t Scene::getGameObjectID(GameObject* gameObject)
{
    return find(gameObjects.begin(), gameObjects.end(), gameObject) - gameObjects.begin();
}

Scene& Scene::operator=(const Scene& other)
{
    deleteAllGameObjects();
    gameObjects.assign(other.gameObjects.begin(), other.gameObjects.end());
    selectedGameObject = other.selectedGameObject;
    return *this;
}

bool Scene::isSelectedGameObject2D()
{
    if (selectedGameObject == nullptr)
    {
        return false;
    }
    return selectedGameObject->is2D();
}

void Scene::setSelectedGameObjectTexture(Texture* texture)
{
    selectedGameObject->setTexture(texture);
}

Texture* Scene::getSelectedGameObjectTexture()
{
    if (selectedGameObject == nullptr)
    {
        return nullptr;
    }
    return selectedGameObject->getTexture();
}

void Scene::deleteAllGameObjects()
{
    for (GameObject* gameObject : nonChildrenGameObjects)
    {
        delete gameObject;
    }
}

void Scene::undo()
{
    history_.undo();
    GameObject * gobj = history_.getSelectedGameObject();
    if (gobj != nullptr)
    {
        setSelectedGameObject(gobj);
    }
}

void Scene::redo()
{
    history_.redo();
    GameObject * gobj = history_.getSelectedGameObject();
    if (gobj != nullptr)
    {
        setSelectedGameObject(gobj);
    }
}

Scene::~Scene()
{
    deleteAllGameObjects();
    nonChildrenGameObjects.clear();
    gameObjects.clear();
}
