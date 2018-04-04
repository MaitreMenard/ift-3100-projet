#pragma once
#include <ctime>
#include "ofMain.h"
#include "ofxGui.h"
#include "grid_plane.h"
#include "scene.h"
#include "gameobjects/cube.h"
#include "gameobjects/sphere.h"
#include "gameobjects/triangle.h"
#include "gameobjects/rectangle.h"
#include "gameobjects/line.h"
#include "gameobjects/polygone.h"
#include "gameobjects/model3D.h"
#include "gameobjects/arrow.h"
#include "gameobjects/star.h"
#include "gui/colorpicker.h"
#include "gui/gameobject_selector.h"
#include "gui/parentIntField.h"
#include "gui/rotation_slider.h"
#include "gui/texture_selector.h"
#include "gui/vec3f_textfield.h"


class ofApp : public ofBaseApp
{
private:
    const float POSITION_MIN_VALUE = -1000;
    const float POSITION_MAX_VALUE = 1000;
    const float ROTATION_MIN_VALUE = -180;
    const float ROTATION_MAX_VALUE = 180;
    const float SCALE_MIN_VALUE = -100;
    const float SCALE_MAX_VALUE = 100;

    const string positionText = "Position: ";
    const string rotationText = "Rotation: ";
    const string scaleText = "Scale: ";

    const string cubeText = "Cube";
    const string sphereText = "Sphere";
    const string rectangleText = "Rectangle";
    const string triangleText = "Triangle";
    const string pentagonText = "Pentagon";
    const string circleText = "Circle";
    const string lineText = "Line";
    const string arrowText = "Arrow";
    const string starText = "Star";
    const string falconText = "Millenium Falcon";
    const string xwingText = "XWing";

    const string inspectorText = "Inspector";

    const string exceptionChildParent = "You cannot set the parent of an object to one of its children.";
    const string exceptionParentItself = "You cannot set the parent of an object to itself.";

    const ofColor headerLabelColor = ofColor(24, 120, 24);

    bool shiftIsPressed;
    bool CtrlIsPressed;
    bool GUIIsDisplayed;

    ofCamera camera;
    GridPlane gridPlane;
    Scene scene;

    Vec3fTextField positionFields;
    RotationSlider rotation;
    Vec3fTextField scaleFields;
    ColorPicker colorPicker;
    ParentIntField parentField;
    
    ofxPanel guiInspector;
    GameObjectSelector gameObjectSelector;
    TextureSelector textureSelector;

    bool guiIsSetup = false;

    void takeScreenShot();

    void addNewGameObject(size_t shapeType);

    void setupGUIInspector();
    void updateGUIInspector();

    void onSelectedGameObjectChange(size_t& selectedGameObjectID);
    void onSelectedGameObjectTextureChange(size_t& selectedTextureID);
    void onSelectedGameObjectPositionChange(ofVec3f& newPosition);
    void onSelectedGameObjectRotationChange(ofVec3f& newRotation);
    void onSelectedGameObjectScaleChange(ofVec3f& newScale);
    void onSelectedGameObjectColorChange(ofColor& newColor);
    void onParentChanged(int & newParentID);

    void setupCamera();

public:
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

enum ShapeType
{
    Shape_Sphere,
    Shape_Cube,
    Shape_Line,
    Shape_Triangle,
    Shape_Rectangle,
    Shape_Pentagon,
    Shape_Circle,
    Shape_Arrow,
    Shape_Star,
    Shape_Falcon,
    Shape_XWing
};
