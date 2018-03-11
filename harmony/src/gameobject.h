#pragma once
#include <vector>
#include "ofMain.h"
#include "transform.h"

class GameObject
{
private:
    void deleteAllChildren();

protected:
    ofTexture texture;
    Transform transform;
    std::vector<GameObject*> children;
    ofMesh model;
    GameObject* parentGameObject;
    ofBoxPrimitive boundingBox;
    size_t nbVertex;
    bool isSelected;
    bool gameObjectIs2D;
    size_t textureID;

    virtual void drawBoundingBox();

public:
    GameObject();
    GameObject(const GameObject& other);

    virtual void setup();
    virtual void update();
    virtual void draw();

    ofVec3f getPosition();
    void setPosition(float x, float y, float z);
    void translate(float dx, float dy, float dz);

    ofQuaternion getRotation();
    void setRotation(float x, float y, float z);
    void rotate(float degrees, float x, float y, float z);

    ofVec3f getScale();
    void setScale(float x, float y, float z);
    void reScale(float x, float y, float z);

    virtual ofColor getColor();
    virtual void setColor(ofColor color);

    void addChild(GameObject* child);
    GameObject* getChild(size_t index);
    void removeChild(size_t index);
    void removeChild(GameObject* childToRemove);
    bool hasChildren();
    vector<GameObject *> getChildren();
    void setChildren(vector<GameObject *>);

    GameObject* getParentGameObject();
    void setParentGameObject(GameObject* parent);

    void setSelected(bool isSelected);

    Transform getTransform() { return Transform(transform); };
    void setTransform(const Transform &transf) { transform = Transform(transf); };

    GameObject& operator=(const GameObject& other);

    size_t getTextureID();
    void setTexture(size_t textureID, ofPixels * pixels);

    bool is2D();

    virtual ~GameObject();
};
