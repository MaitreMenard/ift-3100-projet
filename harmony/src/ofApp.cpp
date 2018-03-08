#include "ofApp.h"

//TODO: transfer all the rendering details into an AppRenderer class

void ofApp::setup()
{
    shiftIsPressed = false;

    ofSetFrameRate(60);
    ofEnableDepthTest();
    ofDisableArbTex();
    ofEnableAlphaBlending();

    camera.setNearClip(0.1f);
    camera.setPosition(0, 2, 5);
    camera.lookAt(ofVec3f(0, 0, 0));

    gridPlane.setup();
    scene.setup();

    Cube* cube = new Cube();
    scene.addGameObject(cube);

    ofSetVerticalSync(true);

    gui.setup();

    position_label.setBackgroundColor(ofColor(48, 48, 72));
    position_x.addListener(this, &ofApp::xPositionChanged);
    position_y.addListener(this, &ofApp::yPositionChanged);
    position_z.addListener(this, &ofApp::zPositionChanged);
    gui.add(position_label.setup(ofParameter<string>("Position")));
    gui.add(position_x.setup("X: ", "0"));
    gui.add(position_y.setup("Y: ", "0"));
    gui.add(position_z.setup("Z: ", "0"));

    gui.add(rotation.setup("Rotation", ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), ofVec3f(360, 360, 360)));
    rotation.setHeaderBackgroundColor(ofColor(48, 48, 72));

    scale_label.setBackgroundColor(ofColor(48, 48, 72));
    scale_x.addListener(this, &ofApp::xScaleChanged);
    scale_y.addListener(this, &ofApp::yScaleChanged);
    scale_z.addListener(this, &ofApp::zScaleChanged);
    gui.add(scale_label.setup(ofParameter<string>("Scale")));
    gui.add(scale_x.setup("X: ", "1"));
    gui.add(scale_y.setup("Y: ", "1"));
    gui.add(scale_z.setup("Z: ", "1"));

    rgb_label.setBackgroundColor(ofColor(48, 48, 72));
    RGB_r.addListener(this, &ofApp::colorChangedRGB);
    RGB_g.addListener(this, &ofApp::colorChangedRGB);
    RGB_b.addListener(this, &ofApp::colorChangedRGB);
    RGB_a.addListener(this, &ofApp::colorChangedRGB);
    gui.add(rgb_label.setup(ofParameter<string>("RGB")));
    gui.add(RGB_r.setup("R: ", 255, 0, 255));
    gui.add(RGB_g.setup("G: ", 255, 0, 255));
    gui.add(RGB_b.setup("B: ", 255, 0, 255));
    gui.add(RGB_a.setup("A: ", 255, 0, 255));

    hsb_label.setBackgroundColor(ofColor(48, 48, 72));
    HSB_h.addListener(this, &ofApp::colorChangedHSB);
    HSB_s.addListener(this, &ofApp::colorChangedHSB);
    HSB_b.addListener(this, &ofApp::colorChangedHSB);
    HSB_a.addListener(this, &ofApp::colorChangedHSB);
    gui.add(hsb_label.setup(ofParameter<string>("HSB")));
    gui.add(HSB_h.setup("H: ", 0, 0, 255));
    gui.add(HSB_s.setup("S: ", 0, 0, 255));
    gui.add(HSB_b.setup("B: ", 255, 0, 255));
    gui.add(HSB_a.setup("A: ", 255, 0, 255));

    gui.setPosition(ofGetWidth() - gui.getWidth() - 2, 2);

    bHide = false;
}

void ofApp::exit()
{}

void ofApp::colorChangedRGB(int & value) {
    scene.setColorSelectedGameObject(ofColor(RGB_r, RGB_g, RGB_b, RGB_a));
   
    HSB_h.removeListener(this, &ofApp::colorChangedHSB);
    HSB_s.removeListener(this, &ofApp::colorChangedHSB);
    HSB_b.removeListener(this, &ofApp::colorChangedHSB);
    HSB_a.removeListener(this, &ofApp::colorChangedHSB);
    
    ofColor currentColor = scene.getColorSelectedGameObject();
    HSB_h = currentColor.getHue();
    HSB_s = currentColor.getSaturation();
    HSB_b = currentColor.getBrightness();
    HSB_a = currentColor.a;

    HSB_h.addListener(this, &ofApp::colorChangedHSB);
    HSB_s.addListener(this, &ofApp::colorChangedHSB);
    HSB_b.addListener(this, &ofApp::colorChangedHSB);
    HSB_a.addListener(this, &ofApp::colorChangedHSB);
}

void ofApp::colorChangedHSB(int & value) {
    ofColor newColor = ofColor(0);
    newColor.setHsb(HSB_h, HSB_s, HSB_b, HSB_a);
    scene.setColorSelectedGameObject(newColor);
    
    RGB_r.removeListener(this, &ofApp::colorChangedRGB);
    RGB_g.removeListener(this, &ofApp::colorChangedRGB);
    RGB_b.removeListener(this, &ofApp::colorChangedRGB);
    RGB_a.removeListener(this, &ofApp::colorChangedRGB);

    ofColor currentColor = scene.getColorSelectedGameObject();
    RGB_r = currentColor.r;
    RGB_g = currentColor.g;
    RGB_b = currentColor.b;
    RGB_a = currentColor.a;

    RGB_r.addListener(this, &ofApp::colorChangedRGB);
    RGB_g.addListener(this, &ofApp::colorChangedRGB);
    RGB_b.addListener(this, &ofApp::colorChangedRGB);
    RGB_a.addListener(this, &ofApp::colorChangedRGB);
}

void ofApp::xPositionChanged(string & value)
{
    float fValue;
    try {
        fValue = stof(value);
        if (fValue < POSITION_MIN_VALUE) {
            fValue = POSITION_MIN_VALUE;
        }
        else if (fValue > POSITION_MAX_VALUE) {
            fValue = POSITION_MAX_VALUE;
        }
        scene.setPositionSelectedGameObject(fValue, POSITION_MIN_VALUE - 1, POSITION_MIN_VALUE - 1);
    }
    catch (...) {
        cout << value << " is not a valid input (xPositionChanged)" << endl;
        scene.setPositionSelectedGameObject(0, POSITION_MIN_VALUE - 1, POSITION_MIN_VALUE - 1);
    }
}

void ofApp::yPositionChanged(string & value)
{
    float fValue;
    try {
        fValue = stof(value);
        if (fValue < POSITION_MIN_VALUE) {
            fValue = POSITION_MIN_VALUE;
        }
        else if (fValue > POSITION_MAX_VALUE) {
            fValue = POSITION_MAX_VALUE;
        }
        scene.setPositionSelectedGameObject(POSITION_MIN_VALUE - 1, fValue, POSITION_MIN_VALUE - 1);
    }
    catch (...) {
        cout << value << " is not a valid input (yPositionChanged)" << endl;
        scene.setPositionSelectedGameObject(POSITION_MIN_VALUE - 1, 0, POSITION_MIN_VALUE - 1);
    }
}

void ofApp::zPositionChanged(string & value)
{
    float fValue;
    try {
        fValue = stof(value);
        if (fValue < POSITION_MIN_VALUE) {
            fValue = POSITION_MIN_VALUE;
        }
        else if (fValue > POSITION_MAX_VALUE) {
            fValue = POSITION_MAX_VALUE;
        }
        scene.setPositionSelectedGameObject(POSITION_MIN_VALUE - 1, POSITION_MIN_VALUE - 1, fValue);
    }
    catch (...) {
        cout << value << " is not a valid input (zPositionChanged)" << endl;
        scene.setPositionSelectedGameObject(POSITION_MIN_VALUE - 1, POSITION_MIN_VALUE - 1, 0);
    }
}

void ofApp::xScaleChanged(string & value)
{
    float fValue;
    try {
        fValue = stof(value);
        if (fValue < SCALE_MIN_VALUE) {
            fValue = SCALE_MIN_VALUE;
        }
        else if (fValue > SCALE_MAX_VALUE) {
            fValue = SCALE_MAX_VALUE;
        }
        scene.setScaleSelectedGameObject(fValue, SCALE_MIN_VALUE - 1, SCALE_MIN_VALUE - 1);
    }
    catch (...) {
        cout << value << " is not a valid input (xScaleChanged)" << endl;
        scene.setScaleSelectedGameObject(1, SCALE_MIN_VALUE - 1, SCALE_MIN_VALUE - 1);
    }
}

void ofApp::yScaleChanged(string & value)
{
    float fValue;
    try {
        fValue = stof(value);
        if (fValue < SCALE_MIN_VALUE) {
            fValue = SCALE_MIN_VALUE;
        }
        else if (fValue > SCALE_MAX_VALUE) {
            fValue = SCALE_MAX_VALUE;
        }
        scene.setScaleSelectedGameObject(SCALE_MIN_VALUE - 1, fValue, SCALE_MIN_VALUE - 1);
    }
    catch (...) {
        cout << value << " is not a valid input (yScaleChanged)" << endl;
        scene.setScaleSelectedGameObject(SCALE_MIN_VALUE - 1, 1, SCALE_MIN_VALUE - 1);
    }
}

void ofApp::zScaleChanged(string & value)
{
    float fValue;
    try {
        fValue = stof(value);
        if (fValue < SCALE_MIN_VALUE) {
            fValue = SCALE_MIN_VALUE;
        }
        else if (fValue > SCALE_MAX_VALUE) {
            fValue = SCALE_MAX_VALUE;
        }
        scene.setScaleSelectedGameObject(SCALE_MIN_VALUE - 1, SCALE_MIN_VALUE - 1, fValue);
    }
    catch (...) {
        cout << value << " is not a valid input (zScaleChanged)" << endl;
        scene.setScaleSelectedGameObject(SCALE_MIN_VALUE - 1, SCALE_MIN_VALUE - 1, 1);
    }
}

void ofApp::update()
{
    scene.update();
    scene.updateSelectedGameObjectRotation(rotation);
}

void ofApp::draw()
{
    ofClear(0);

    ofBackgroundGradient(ofColor::white, ofColor::gray);

    camera.begin();
    scene.draw();
    gridPlane.draw();
    camera.end();

    if (!bHide)
    {
        ofDisableDepthTest();
        gui.draw();
        ofEnableDepthTest();
    }
}

void ofApp::takeScreenShot()
{
    time_t secondsSinceEpoch = time(0);
    tm* now = localtime(&secondsSinceEpoch);

    std::stringstream ss;
    ss << now->tm_year + 1900 << '-' << now->tm_mon + 1 << '-' << now->tm_mday << '_' <<
        now->tm_hour << 'h' << now->tm_min << 'm' << now->tm_sec << "s.png";
    std::string fileName = ss.str();

    ofImage image;
    image.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    image.save(fileName);

    ofLog() << "screenshot saved to: " << fileName;
}

void ofApp::keyPressed(int key)
{
    switch (key)
    {
    case ' ':
        takeScreenShot();
        break;
    case '+':
        camera.move(0, 0, -1);
        break;
    case '-':
        camera.move(0, 0, 1);
        break;
    case 356:   // left arrow
        camera.pan(10);
        break;
    case 357:   // up arrow
        camera.tilt(10);
        break;
    case 358:   // right arrow
        camera.pan(-10);
        break;
    case 359:   // down arrow
        camera.tilt(-10);
        break;
    case 'w':
        camera.move(0, 1, 0);
        break;
    case 'a':
        camera.move(-1, 0, 0);
        break;
    case 's':
        camera.move(0, -1, 0);
        break;
    case 'd':
        camera.move(1, 0, 0);
        break;
    case 2304:  // shift
        shiftIsPressed = true;
        break;
    case 'h':
        bHide = !bHide;
        break;
    default:
        break;
    }
}

void ofApp::keyReleased(int key)
{
    switch (key)
    {
    case 2304:  // shift
        shiftIsPressed = false;
        break;
    default:
        break;
    }
}

void ofApp::mouseMoved(int x, int y)
{

}

void ofApp::mouseDragged(int x, int y, int button)
{

}

void ofApp::mousePressed(int x, int y, int button)
{

}

void ofApp::mouseReleased(int x, int y, int button)
{

}

void ofApp::mouseEntered(int x, int y)
{

}

void ofApp::mouseExited(int x, int y)
{

}

void ofApp::windowResized(int w, int h)
{

}

void ofApp::gotMessage(ofMessage msg)
{

}

void ofApp::dragEvent(ofDragInfo dragInfo)
{

}
