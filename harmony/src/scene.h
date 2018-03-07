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
    void draw();

    void addGameObject(GameObject* gameObject);
    void translateSelectedGameObject(float dx, float dy, float dz);
    void rescaleSelectedGameObject(float x, float y, float z);
	void rotateSelectedGameObject(float dx, float dy, float dz);

    Scene& operator=(const Scene& other);

    ~Scene();
};