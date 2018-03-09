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

class ofApp : public ofBaseApp
{
private:
    const float SCALE_MIN_VALUE = -100;
    const float SCALE_MAX_VALUE = 100;
    const float POSITION_MIN_VALUE = -1000;
    const float POSITION_MAX_VALUE = 1000;

    bool shiftIsPressed;

    ofCamera camera;
    GridPlane gridPlane;
    Scene scene;

    vector<ofxButton*> object_buttons;

    texelFactory tFac;

public:
    ~ofApp();
    void setup();
    void update();
    void draw();

    void exit();
    void takeScreenShot();

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

    void xPositionChanged(string & value);
    void yPositionChanged(string & value);
    void zPositionChanged(string & value);

    void xScaleChanged(string & value);
    void yScaleChanged(string & value);
    void zScaleChanged(string & value);

    void colorChangedRGB(int & value);
    void colorChangedHSB(int & value);

    void parentChanged(int & newParentID);

    void addNewGameObject(int gameObjectType);

    void setupGUIInspector();
    void setupGUIInspector(int buttonID);

    void checkIfAButtonIsPressed();

    bool bHide;

    ofxTextField position_x;
    ofxTextField position_y;
    ofxTextField position_z;

    ofxVec3Slider rotation;

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
};
