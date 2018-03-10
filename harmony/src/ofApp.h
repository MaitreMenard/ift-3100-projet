#pragma once
#include <ctime>
#include "ofMain.h"
#include "grid_plane.h"
#include "scene.h"
#include "cube.h"
#include "sphere.h"
#include "ofxGui.h"
#include "ofxInputField.h"
#include "plan2D.h"
#include "texelFactory.h"
#include "gui/rotation_slider.h"

class ofApp : public ofBaseApp
{
private:
    const float SCALE_MIN_VALUE = -100;
    const float SCALE_MAX_VALUE = 100;
    const float POSITION_MIN_VALUE = -1000;
    const float POSITION_MAX_VALUE = 1000;

    const string aText = "A: ";
    const string bText = "B: ";
    const string gText = "G: ";
    const string hText = "H: ";
    const string rText = "R: ";
    const string sText = "S: ";
    const string xText = "X: ";
    const string yText = "Y: ";
    const string zText = "Z: ";
    const string hsbText = "HSB";
    const string rgbText = "RGB";
    const string parentText = "Parent: ";
    const string positionText = "Position: ";
    const string rotationText = "Rotation: ";
    const string scaleText = "Scale: ";

    const string cubeText = "Cube";
    const string sphereText = "Sphere";

    const string exceptionChildParent = "You cannot set the parent of an object to one of its children.";
    const string exceptionParentItself = "You cannot set the parent of an object to itself.";
    const string exceptionInvalidInput = " is not a valid input.";

    const ofColor baseButtonColor = ofColor(24, 24, 24);
    const ofColor baseLabelColor = ofColor(48, 48, 72);
    const ofColor highlightedButtonColor = ofColor(24, 24, 240);

    bool shiftIsPressed;
    bool GUIIsDisplayed;

    ofCamera camera;
    GridPlane gridPlane;
    Scene scene;

    vector<ofxButton*> object_buttons;

    texelFactory tFac;

    ofxTextField position_x;
    ofxTextField position_y;
    ofxTextField position_z;

    RotationSlider rotation;

    ofxTextField scale_x;
    ofxTextField scale_y;
    ofxTextField scale_z;

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

    ofxLabel scale_label;
    ofxLabel position_label;
    ofxLabel rgb_label;
    ofxLabel hsb_label;

    bool guiIsSetup = false;

    void takeScreenShot();

    float convertTextFieldValueToFloat(string stringValue, float minValue, float maxValue);

    void xPositionChanged(string & value);
    void yPositionChanged(string & value);
    void zPositionChanged(string & value);

    void rotationChanged(ofVec3f eulerAngles);

    void xScaleChanged(string & value);
    void yScaleChanged(string & value);
    void zScaleChanged(string & value);

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

    void checkIfAButtonIsPressed();

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

enum ShapeType {
    Shape_Sphere,
    Shape_Cube
};
