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

    /*Sphere* sphere = new Sphere();
    sphere->translate(0.0f, 2.0f, 0.0f);
    scene.addGameObject(sphere);*/
    /*Cube* cube = new Cube();
    Cube* cube2 = new Cube();
    cube->addChild(cube2);
    cube2->reScale(0.5f, 0.5f, 0.5f);
    cube2->translate(0.0f, 1.0f, 0.0f);
    scene.addGameObject(cube);*/

    /*Sphere* sphere = new Sphere();
    plan2D* plan = new plan2D();

    sphere->translate(0.0f, 2.0f, 0.0f);
    scene.addGameObject(sphere);
    scene.addGameObject(plan);

    // Test procedural texture
    ofPixels * pix = new ofPixels();
    pix->allocate(500, 500, OF_PIXELS_RGB);
    scene.getGameObject(1)->setTexture(tFac.setMarbleTexture(pix, 5.0, 5.0, 1.0, 16.0));*/

    //Cube* cube = new Cube();
    //Cube* cube2 = new Cube();
    //cube->addChild(cube2);
    //cube2->reScale(0.5f, 0.5f, 0.5f);
    //cube2->translate(0.0f, 1.0f, 0.0f);
    //scene.addGameObject(cube);

    ofSetVerticalSync(true);

    //SCENE
    guiScene.setup();

    bHide = false;
}

void ofApp::setupGUIInspector() {
    setupGUIInspector(scene.getSelectedGameObjectID());
}

void ofApp::setupGUIInspector(int buttonID) {
    object_buttons.at(scene.getSelectedGameObjectID())->setBackgroundColor(ofColor(24, 24, 24));
    scene.setSelectedGameObject(buttonID);

    //INSPECTOR
    object_buttons.at(buttonID)->setBackgroundColor(ofColor(24, 24, 240));

    guiInspector.clear();
    guiInspector.setup();

    position_label.setBackgroundColor(ofColor(48, 48, 72));
    position_x.removeListener(this, &ofApp::xPositionChanged);
    position_y.removeListener(this, &ofApp::yPositionChanged);
    position_z.removeListener(this, &ofApp::zPositionChanged);
    guiInspector.add(position_label.setup(ofParameter<string>("Position")));
    ofVec3f selectedGameObjectPosition = scene.getPositionSelectedGameObject();
    guiInspector.add(position_x.setup("X: ", to_string(selectedGameObjectPosition.x)));
    guiInspector.add(position_y.setup("Y: ", to_string(selectedGameObjectPosition.y)));
    guiInspector.add(position_z.setup("Z: ", to_string(selectedGameObjectPosition.z)));
    position_x.addListener(this, &ofApp::xPositionChanged);
    position_y.addListener(this, &ofApp::yPositionChanged);
    position_z.addListener(this, &ofApp::zPositionChanged);

    ofVec3f selectedGameObjectRotation = scene.getEulerRotationSelectedGameObject();
    guiInspector.add(rotation.setup("Rotation", selectedGameObjectRotation, ofVec3f(0, 0, 0), ofVec3f(360, 360, 360)));
    rotation.setHeaderBackgroundColor(ofColor(48, 48, 72));

    scale_label.setBackgroundColor(ofColor(48, 48, 72));
    scale_x.removeListener(this, &ofApp::xScaleChanged);
    scale_y.removeListener(this, &ofApp::yScaleChanged);
    scale_z.removeListener(this, &ofApp::zScaleChanged);
    guiInspector.add(scale_label.setup(ofParameter<string>("Scale")));
    ofVec3f selectedGameObjectScale = scene.getScaleSelectedGameObject();
    guiInspector.add(scale_x.setup("X: ", to_string(selectedGameObjectScale.x)));
    guiInspector.add(scale_y.setup("Y: ", to_string(selectedGameObjectScale.y)));
    guiInspector.add(scale_z.setup("Z: ", to_string(selectedGameObjectScale.z)));
    scale_x.addListener(this, &ofApp::xScaleChanged);
    scale_y.addListener(this, &ofApp::yScaleChanged);
    scale_z.addListener(this, &ofApp::zScaleChanged);

    rgb_label.setBackgroundColor(ofColor(48, 48, 72));
    RGB_r.removeListener(this, &ofApp::colorChangedRGB);
    RGB_g.removeListener(this, &ofApp::colorChangedRGB);
    RGB_b.removeListener(this, &ofApp::colorChangedRGB);
    RGB_a.removeListener(this, &ofApp::colorChangedRGB);
    guiInspector.add(rgb_label.setup(ofParameter<string>("RGB")));
    ofColor selectedGameObjectColor = scene.getColorSelectedGameObject();
    guiInspector.add(RGB_r.setup("R: ", selectedGameObjectColor.r, 0, 255));
    guiInspector.add(RGB_g.setup("G: ", selectedGameObjectColor.g, 0, 255));
    guiInspector.add(RGB_b.setup("B: ", selectedGameObjectColor.b, 0, 255));
    guiInspector.add(RGB_a.setup("A: ", selectedGameObjectColor.a, 0, 255));
    RGB_r.addListener(this, &ofApp::colorChangedRGB);
    RGB_g.addListener(this, &ofApp::colorChangedRGB);
    RGB_b.addListener(this, &ofApp::colorChangedRGB);
    RGB_a.addListener(this, &ofApp::colorChangedRGB);

    hsb_label.setBackgroundColor(ofColor(48, 48, 72));
    HSB_h.removeListener(this, &ofApp::colorChangedHSB);
    HSB_s.removeListener(this, &ofApp::colorChangedHSB);
    HSB_b.removeListener(this, &ofApp::colorChangedHSB);
    HSB_a.removeListener(this, &ofApp::colorChangedHSB);
    guiInspector.add(hsb_label.setup(ofParameter<string>("HSB")));
    guiInspector.add(HSB_h.setup("H: ", selectedGameObjectColor.getHue(), 0, 255));
    guiInspector.add(HSB_s.setup("S: ", selectedGameObjectColor.getSaturation(), 0, 255));
    guiInspector.add(HSB_b.setup("B: ", selectedGameObjectColor.getBrightness(), 0, 255));
    guiInspector.add(HSB_a.setup("A: ", selectedGameObjectColor.a, 0, 255));
    HSB_h.addListener(this, &ofApp::colorChangedHSB);
    HSB_s.addListener(this, &ofApp::colorChangedHSB);
    HSB_b.addListener(this, &ofApp::colorChangedHSB);
    HSB_a.addListener(this, &ofApp::colorChangedHSB);

    parent.removeListener(this, &ofApp::parentChanged);
    parent.setBackgroundColor(ofColor(48, 48, 72));
    guiInspector.add(parent.setup("Parent: ", scene.getSelectedGameObjectParentID(), 0, object_buttons.size()));
    parent.addListener(this, &ofApp::parentChanged);

    guiInspector.setPosition(ofGetWidth() - guiInspector.getWidth() - 2, 2);
}

void ofApp::exit()
{}

void ofApp::parentChanged(int & newParentID) {
    if (newParentID - 1 == scene.getSelectedGameObjectID()) {
        cout << "You cannot set the parent of an object to itself." << endl;
    }
    else if (scene.isNewParentIDInSelectedGameObjectChildren(newParentID)) {
        cout << "You cannot set the parent of an object to one of its children." << endl;
    }
    else {
        scene.setSelectedGameObjectParent(newParentID);
    }
}

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
    checkIfAButtonIsPressed();
    scene.update();
    scene.updateSelectedGameObjectRotation(rotation);
}

void ofApp::checkIfAButtonIsPressed() {
    for (int i = 0; i < object_buttons.size(); i++)
    {
        if (*object_buttons[i]) {
            if (scene.getSelectedGameObjectID() != i) {
                setupGUIInspector(i);
            }
            break;
        }
    }
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
        guiInspector.draw();
        guiScene.draw();
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
    ofPixels * pix;
    switch (key)
    {
    case 'p':
        /*pix = new ofPixels();
        pix->allocate(500, 500, OF_PIXELS_RGB);
        scene.getGameObject(1)->setTexture(tFac.setMarbleTexture(pix, 2.0, 2.0, 1.0, 16.0));*/
        break;
    case ' ':
        takeScreenShot();
        break;
    case '+':
        camera.dolly(-1);
        break;
    case '-':
        camera.dolly(1);
        break;
    case 356:   // left arrow
        camera.pan(5);
        break;
    case 357:   // up arrow
        camera.tilt(5);
        break;
    case 358:   // right arrow
        camera.pan(-5);
        break;
    case 359:   // down arrow
        camera.tilt(-5);
        break;
    case 'w':
        camera.boom(1);
        break;
    case 'a':
        camera.truck(-1);
        break;
    case 's':
        camera.boom(-1);
        break;
    case 'd':
        camera.truck(1);
        break;
    case 2304:  // shift
        shiftIsPressed = true;
        break;
    case 'h':
        bHide = !bHide;
        break;
    case 'i':
        addNewGameObject(0);
        break;
    case 'o':
        addNewGameObject(1);
        break;
    default:
        break;
    }
}

void ofApp::addNewGameObject(int gameObjectType) {
    ofxButton *object_button = new ofxButton();
    object_buttons.push_back(object_button);
    string shapeName;
    GameObject *gameObject;
    if (gameObjectType == 0) {
        gameObject = new Sphere();
        shapeName = "Sphere ";
    }
    else if (gameObjectType == 1) {
        gameObject = new Cube();
        shapeName = "Cube ";
    }
    guiScene.add(object_button->setup(ofParameter<string>(shapeName)));
    scene.addGameObject(gameObject);
    setupGUIInspector(object_buttons.size() - 1);
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

ofApp::~ofApp() {
    for (ofxButton* button : object_buttons)
    {
        delete button;
    }
    object_buttons.clear();
}
