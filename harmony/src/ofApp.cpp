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

void ofApp::setupGUIInspector(int shapeID) {
    if (object_labels[shapeID] != nullptr) {
        //INSPECTOR
        object_labels[selectedShapeID]->setBackgroundColor(ofColor(24, 24, 24));
        object_labels[shapeID]->setBackgroundColor(ofColor(24, 24, 240));

        selectedShapeID = shapeID;

        guiInspector.clear();
        guiInspector.setup();

        position_label.setBackgroundColor(ofColor(48, 48, 72));
        position_x.addListener(this, &ofApp::xPositionChanged);
        position_y.addListener(this, &ofApp::yPositionChanged);
        position_z.addListener(this, &ofApp::zPositionChanged);
        guiInspector.add(position_label.setup(ofParameter<string>("Position")));
        ofVec3f shapePosition = scene.getPositionSelectedGameObject(shapeID);
        guiInspector.add(position_x.setup("X: ", "0"));
        guiInspector.add(position_y.setup("Y: ", "0"));
        guiInspector.add(position_z.setup("Z: ", "0"));

        guiInspector.add(rotation.setup("Rotation", ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), ofVec3f(360, 360, 360)));
        rotation.setHeaderBackgroundColor(ofColor(48, 48, 72));

        scale_label.setBackgroundColor(ofColor(48, 48, 72));
        scale_x.addListener(this, &ofApp::xScaleChanged);
        scale_y.addListener(this, &ofApp::yScaleChanged);
        scale_z.addListener(this, &ofApp::zScaleChanged);
        guiInspector.add(scale_label.setup(ofParameter<string>("Scale")));
        guiInspector.add(scale_x.setup("X: ", "1"));
        guiInspector.add(scale_y.setup("Y: ", "1"));
        guiInspector.add(scale_z.setup("Z: ", "1"));

        rgb_label.setBackgroundColor(ofColor(48, 48, 72));
        RGB_r.addListener(this, &ofApp::colorChangedRGB);
        RGB_g.addListener(this, &ofApp::colorChangedRGB);
        RGB_b.addListener(this, &ofApp::colorChangedRGB);
        RGB_a.addListener(this, &ofApp::colorChangedRGB);
        guiInspector.add(rgb_label.setup(ofParameter<string>("RGB")));
        guiInspector.add(RGB_r.setup("R: ", 255, 0, 255));
        guiInspector.add(RGB_g.setup("G: ", 255, 0, 255));
        guiInspector.add(RGB_b.setup("B: ", 255, 0, 255));
        guiInspector.add(RGB_a.setup("A: ", 255, 0, 255));

        hsb_label.setBackgroundColor(ofColor(48, 48, 72));
        HSB_h.addListener(this, &ofApp::colorChangedHSB);
        HSB_s.addListener(this, &ofApp::colorChangedHSB);
        HSB_b.addListener(this, &ofApp::colorChangedHSB);
        HSB_a.addListener(this, &ofApp::colorChangedHSB);
        guiInspector.add(hsb_label.setup(ofParameter<string>("HSB")));
        guiInspector.add(HSB_h.setup("H: ", 0, 0, 255));
        guiInspector.add(HSB_s.setup("S: ", 0, 0, 255));
        guiInspector.add(HSB_b.setup("B: ", 255, 0, 255));
        guiInspector.add(HSB_a.setup("A: ", 255, 0, 255));

        parent.setBackgroundColor(ofColor(48, 48, 72));
        parent.addListener(this, &ofApp::parentChanged);
        guiInspector.add(parent.setup("Parent: ", -1, -1, 9));

        guiInspector.setPosition(ofGetWidth() - guiInspector.getWidth() - 2, 2);
    }
}

void ofApp::exit()
{}

void ofApp::parentChanged(int & newParentID) {
    //TODO: Set parent ID in gameobject
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
		pix = new ofPixels();
		pix->allocate(500, 500, OF_PIXELS_RGB);
		scene.getGameObject(1)->setTexture(tFac.setMarbleTexture(pix, 2.0, 2.0, 1.0, 16.0));
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
    case 'o':
        addNewShape(0);
        break;
    case 'p':
        addNewShape(1);
        break;
    case '0':
        setupGUIInspector(0);
        break;
    case '1':
        setupGUIInspector(1);
        break;
    case '2':
        setupGUIInspector(2);
        break;
    case '3':
        setupGUIInspector(3);
        break;
    case '4':
        setupGUIInspector(4);
        break;
    case '5':
        setupGUIInspector(5);
        break;
    case '6':
        setupGUIInspector(6);
        break;
    case '7':
        setupGUIInspector(7);
        break;
    case '8':
        setupGUIInspector(8);
        break;
    case '9':
        setupGUIInspector(9);
        break;
    default:
        break;
    }
}

void ofApp::addNewShape(int shape) {
    for (int i = 0; i < MAXIMUM_SHAPES; i++) {
        if (object_labels[i] == nullptr) {
            ofxLabel *object_label = new ofxLabel();
            object_labels[i] = object_label;
            string shapeName;
            GameObject *gameObject;
            if (shape == 0) {
                gameObject = new Sphere();
                shapeName = "Sphere ";
            }
            else if (shape == 1) {
                gameObject = new Cube();
                shapeName = "Cube ";
            }
            guiScene.add(object_label->setup(ofParameter<string>(shapeName + to_string(i))));
            scene.addGameObject(gameObject);
            setupGUIInspector(i);
            break;
        }
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

ofApp::~ofApp() {
    for (int i = 0; i < MAXIMUM_SHAPES; i++)
    {
        delete object_labels[i];
    }
}
