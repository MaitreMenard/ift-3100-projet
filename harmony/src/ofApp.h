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
	texelFactory tFac;

public:
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

    void colorTypeChanged(bool & pressed);

    void updateUIValues(ofxInputField<string> & field, int & key);

    void xPositionChanged(string & value);
    void yPositionChanged(string & value);
    void zPositionChanged(string & value);

    void xScaleChanged(string & value);
    void yScaleChanged(string & value);
    void zScaleChanged(string & value);

    bool bHide;

    ofxTextField scale_x;
    ofxTextField scale_y;
    ofxTextField scale_z;

    ofxTextField position_x;
    ofxTextField position_y;
    ofxTextField position_z;

    ofxColorSlider color;
    ofxVec3Slider rotation;
    ofxToggle colorType;

    ofxPanel gui;

    ofxLabel scale_label;
    ofxLabel position_label;
};
