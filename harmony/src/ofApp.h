#pragma once
#include <ctime>
#include "ofMain.h"
#include "grid_plane.h"
#include "scene.h"
#include "cube.h"
#include "ofxGui.h"
#include "ofxInputField.h"

class ofApp : public ofBaseApp
{
private:
    bool shiftIsPressed;

    ofCamera camera;
    GridPlane gridPlane;
    Scene scene;

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

	bool bHide;

	ofxFloatField scale_x;
	ofxFloatField scale_y;
	ofxFloatField scale_z;

	ofxFloatField position_x;
	ofxFloatField position_y;
	ofxFloatField position_z;

	ofxColorSlider color;
	ofxVec3Slider rotation;
	ofxToggle colorType;

	ofxPanel gui;

	ofxLabel scale_label;
	ofxLabel position_label;
};
