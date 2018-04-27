#pragma once
#include <vector>
#include "ofMain.h"
#include "transform.h"
#include "texture.h"

class GameObjectVisitor;

class GameObject
{
private:
    std::string name;

    void deleteAllChildren();

protected:
    Texture* texture;
    Transform transform;
    ofMaterial material;
    bool hasMaterial = false;
    std::vector<GameObject*> children;
    ofMesh model;
    GameObject* parentGameObject;
    ofBoxPrimitive boundingBox;
    size_t nbVertex;
    bool isSelected;
    bool gameObjectIs2D;

    void drawChildren();
    virtual void drawBoundingBox();

public:
    GameObject(std::string name, Texture* texture);
    GameObject(const GameObject& other);

    virtual void setup();
    virtual void update();
    virtual void draw();
    virtual void drawTextureAndMaterial();

    float getShininess();
    void setShininess(float shininess);
    virtual ofColor getDiffuseColor();
    virtual void setDiffuseColor(ofColor diffuseColor);
    virtual ofColor getSpecularColor();
    virtual void setSpecularColor(ofColor specularColor);
    virtual ofColor getAmbientColor();
    virtual void setAmbientColor(ofColor ambientColor);

    std::string getName();

    virtual ofVec3f getPosition();
    virtual void setPosition(ofVec3f position);
    void translate(float dx, float dy, float dz);

    ofQuaternion getRotation();
    ofVec3f getEulerAngles();
    virtual void setRotation(float x, float y, float z);
    void rotate(float degrees, float x, float y, float z);

    ofVec3f getScale();
    void setScale(ofVec3f scale);
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

    virtual void setSelected(bool isSelected);

    Transform getTransform() { return Transform(transform); };
    void setTransform(const Transform &transf) { transform = Transform(transf); };

    GameObject& operator=(const GameObject& other);

    Texture* getTexture();
    void setTexture(Texture* texture);

    bool is2D();

    virtual void accept(GameObjectVisitor& visitor);

    virtual ~GameObject();
};
