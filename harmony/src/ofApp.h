#pragma once
#include <ctime>
#include "ofMain.h"
#include "ofxGui.h"
#include "grid_plane.h"
#include "scene.h"
#include "textureFactory.h"
#include "gameobjects/light.h"
#include "gui/inspector.h"
#include "gui/gameobject_selector.h"
#include "gui/texture_selector.h"
#include "gui/lightmode_selector.h"
#include "gameobjectFactory.h"
#include "fboRenderer.h"


class ofApp : public ofBaseApp
{
private:
    bool shiftIsPressed;
    bool CtrlIsPressed;
    bool GUIIsDisplayed;
    bool lightIsActive;

    const string lightText = "Light";

    ofFbo fbo;
	ofFbo fboPortal;
    FboRenderer fboRender;

    std::vector<Light*> lights;
    const ofVec3f initialCameraPosition = ofVec3f(0, 2, 5);
    ofCamera camera;
    ofCamera cameraPortal;
    GridPlane gridPlane;
    TextureFactory textureFactory;
    GameObjectFactory gameobjectFactory;
    Scene scene;

    bool portalsWereCreated;
    Mirror* portal1;
    const ofVec3f portal1InitialPosition = ofVec3f(-2, 2, 0);
    Mirror* portal2;
    const ofVec3f portal2InitialPosition = ofVec3f(2, 2, 0);
    const float portalCameraYRotationOffset = 180.f;

    Inspector inspector;
    GameObjectSelector gameObjectSelector;
    TextureSelector textureSelector;
    LightModeSelector lightModeSelector;

    void takeScreenShot();

    GameObject* addNewGameObject(size_t shapeType, Texture* texture);
    void setupNewGameObject(GameObject* gameObject);

    void setupInspector();
    void setupCamera();
    void setupLight(bool enableOrDisable);

    void createLight();
    void enableAllLights();
    void disableAllLights();

    void onSelectedGameObjectChange(GameObject*& selectedGameObject);
    void onSelectedControlPointChange(ControlPoint*& controlPoint);
    void setSelectedGameObject(GameObject* selectedGameObject);
    void onSelectedGameObjectTextureChange(Texture*& texture);
    void onSelectedGameObjectPositionChange(ofVec3f& newPosition);
    void onSelectedGameObjectRotationChange(ofVec3f& newRotation);
    void onSelectedGameObjectScaleChange(ofVec3f& newScale);
    void onSelectedGameObjectColorChange(ofColor& newColor);
    void onSelectedGameObjectDiffuseColorChange(ofColor& diffuseColor);
    void onSelectedGameObjectSpecularColorChange(ofColor& specularColor);
    void onSelectedGameObjectAmbientColorChange(ofColor& ambientColor);
    void onSelectedGameObjectShininessChange(int& shininess);
    void onParentChange(int& newParentID);
    void onSelectedCurveAddControlPoint();
    void onLightModeChange(int& newLightMode);
    void onSpotLightCutOffChange(int& spotCutOff);

    void toggleGUIVisibility();
    void drawGUI();

    void transfertPortalImage(Mirror* imageSender, Mirror* imageReceiver);
    void updatePortalFbo();
    Mirror* createPortal(ofVec3f position);

public:
    ~ofApp();
    void setup();
    void update();
    void draw();
    void exit();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
};
