#pragma once
#include <ctime>
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxInputField.h"
#include "grid_plane.h"
#include "scene.h"
#include "gameobjects/cube.h"
#include "gameobjects/sphere.h"
#include "gameobjects/triangle.h"
#include "gameobjects/rectangle.h"
#include "gameobjects/point.h"
#include "gameobjects/line.h"
#include "gameobjects/polygon.h"
#include "gameobjects/model3D.h"
#include "gui/rotation_slider.h"
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

    const string aText = "A: ";
    const string bText = "B: ";
    const string gText = "G: ";
    const string hText = "H: ";
    const string rText = "R: ";
    const string sText = "S: ";
    const string hsbText = "HSB";
    const string rgbText = "RGB";
    const string parentText = "Parent: ";
    const string positionText = "Position: ";
    const string rotationText = "Rotation: ";
    const string scaleText = "Scale: ";

    const string cubeText = "Cube";
    const string sphereText = "Sphere";
    const string rectangleText = "Rectangle";
    const string triangleText = "Triangle";
    const string pointText = "Point";
    const string polygonText = "Polygon";
    const string lineText = "Line";

    const string noneText = "None";
    const string cloudText = "Cloud";
    const string marbleText = "Marble";
    const string noiseText = "Noise";
    const string turbulenceText = "Turbulence";
    const string woodText = "Wood";
    const string zoomText = "Zoom";

    const string inspectorText = "Inspector";
    const string sceneText = "Scene";
    const string textureText = "Texture";

    const string exceptionChildParent = "You cannot set the parent of an object to one of its children.";
    const string exceptionParentItself = "You cannot set the parent of an object to itself.";

    const ofColor baseButtonColor = ofColor(24, 24, 24);
    const ofColor baseLabelColor = ofColor(48, 48, 72);
    const ofColor headerLabelColor = ofColor(24, 120, 24);
    const ofColor highlightedButtonColor = ofColor(24, 24, 240);

    bool shiftIsPressed;
    bool CtrlIsPressed;
    bool GUIIsDisplayed;

    ofCamera camera;
    GridPlane gridPlane;
    Scene scene;

    vector<ofxButton*> object_buttons;
    vector<ofxButton> texture_buttons;

    Vec3fTextField positionFields;
    RotationSlider rotation;
    Vec3fTextField scaleFields;

    ofxIntField RGB_r;
    ofxIntField RGB_g;
    ofxIntField RGB_b;
    ofxIntField RGB_a;

    ofxIntField HSB_h;
    ofxIntField HSB_s;
    ofxIntField HSB_b;
    ofxIntField HSB_a;

    ofxIntField parent;

    ofxPanel guiInspector;
    ofxPanel guiScene;
    ofxPanel guiTexture;

    ofxLabel rgb_label;
    ofxLabel hsb_label;
    ofxLabel inspector_label;
    ofxLabel scene_label;
    ofxLabel texture_label;

    ofxButton none_button;
    ofxButton cloud_button;
    ofxButton marble_button;
    ofxButton noise_button;
    ofxButton turbulence_button;
    ofxButton wood_button;
    ofxButton zoom_button;

    bool guiIsSetup = false;

    void takeScreenShot();

    void colorChangedRGB(int & value);
    void colorChangedHSB(int & value);
    void addRGBListeners();
    void addHSBListeners();
    void removeRGBListeners();
    void removeHSBListeners();

    void parentChanged(int & newParentID);

    void addNewGameObject(size_t shapeType);

    void setupGUIInspector(size_t buttonID);
    void updateGUIInspector(size_t buttonID);
    void setupGUITexture(size_t textureID);
    void updateGUITexture(size_t textureID);

    void checkIfASceneButtonIsPressed();
    void checkIfATextureButtonIsPressed();

    void setupCamera();

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

enum ShapeType
{
    Shape_Sphere,
    Shape_Cube,
    Shape_Point,
    Shape_Line,
    Shape_Triangle,
    Shape_Rectangle,
    Shape_Polygon
};
