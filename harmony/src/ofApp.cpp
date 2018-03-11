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
    plan2D* plan = new plan2D();
    sphere->translate(0.0f, 2.0f, 0.0f);
    scene.addGameObject(sphere);
    scene.addGameObject(plan);

    // Test procedural texture
    ofPixels * pix = new ofPixels();
    pix->allocate(500, 500, OF_PIXELS_RGB);
    scene.getGameObject(1)->setTexture(tFac.setMarbleTexture(pix, 5.0, 5.0, 1.0, 16.0));*/

    ofSetVerticalSync(true);

    //SCENE
    guiScene.setup();

    GUIIsDisplayed = true;
}

void ofApp::setupGUIInspector(size_t buttonID)
{
    object_buttons.at(scene.getSelectedGameObjectID())->setBackgroundColor(baseButtonColor);
    scene.setSelectedGameObject(buttonID);

    //INSPECTOR
    object_buttons.at(buttonID)->setBackgroundColor(highlightedButtonColor);

    guiInspector.clear();
    guiInspector.setup();

    guiInspector.add(positionFields.setup("Position: ", scene.getPositionSelectedGameObject(),
        ofVec3f(POSITION_MIN_VALUE), ofVec3f(POSITION_MAX_VALUE)));
    std::function<void(ofVec3f)> positionListener = [=](ofVec3f value)
    {
        scene.setPositionSelectedGameObject(value.x, value.y, value.z);
    };
    positionFields.addListener(positionListener);

    guiInspector.add(rotation.setup(rotationText, scene.getEulerRotationSelectedGameObject(),
        ofVec3f(ROTATION_MIN_VALUE), ofVec3f(ROTATION_MAX_VALUE)));
    std::function<void(ofVec3f)> rotationListener = [=](ofVec3f value)
    {
        scene.setRotationSelectedGameObject(value);
    };
    rotation.addListener(rotationListener);

    guiInspector.add(scaleFields.setup("Scale: ", scene.getScaleSelectedGameObject(),
        ofVec3f(SCALE_MIN_VALUE), ofVec3f(SCALE_MAX_VALUE)));
    std::function<void(ofVec3f)> scaleListener = [=](ofVec3f value)
    {
        scene.setScaleSelectedGameObject(value.x, value.y, value.z);
    };
    scaleFields.addListener(scaleListener);

    rgb_label.setBackgroundColor(baseLabelColor);
    RGB_r.removeListener(this, &ofApp::colorChangedRGB);
    RGB_g.removeListener(this, &ofApp::colorChangedRGB);
    RGB_b.removeListener(this, &ofApp::colorChangedRGB);
    RGB_a.removeListener(this, &ofApp::colorChangedRGB);
    guiInspector.add(rgb_label.setup(ofParameter<string>(rgbText)));
    ofColor selectedGameObjectColor = scene.getColorSelectedGameObject();
    guiInspector.add(RGB_r.setup(rText, selectedGameObjectColor.r, 0, 255));
    guiInspector.add(RGB_g.setup(gText, selectedGameObjectColor.g, 0, 255));
    guiInspector.add(RGB_b.setup(bText, selectedGameObjectColor.b, 0, 255));
    guiInspector.add(RGB_a.setup(aText, selectedGameObjectColor.a, 0, 255));
    RGB_r.addListener(this, &ofApp::colorChangedRGB);
    RGB_g.addListener(this, &ofApp::colorChangedRGB);
    RGB_b.addListener(this, &ofApp::colorChangedRGB);
    RGB_a.addListener(this, &ofApp::colorChangedRGB);

    hsb_label.setBackgroundColor(baseLabelColor);
    HSB_h.removeListener(this, &ofApp::colorChangedHSB);
    HSB_s.removeListener(this, &ofApp::colorChangedHSB);
    HSB_b.removeListener(this, &ofApp::colorChangedHSB);
    HSB_a.removeListener(this, &ofApp::colorChangedHSB);
    guiInspector.add(hsb_label.setup(ofParameter<string>(hsbText)));
    guiInspector.add(HSB_h.setup(hText, selectedGameObjectColor.getHue(), 0, 255));
    guiInspector.add(HSB_s.setup(sText, selectedGameObjectColor.getSaturation(), 0, 255));
    guiInspector.add(HSB_b.setup(bText, selectedGameObjectColor.getBrightness(), 0, 255));
    guiInspector.add(HSB_a.setup(aText, selectedGameObjectColor.a, 0, 255));
    HSB_h.addListener(this, &ofApp::colorChangedHSB);
    HSB_s.addListener(this, &ofApp::colorChangedHSB);
    HSB_b.addListener(this, &ofApp::colorChangedHSB);
    HSB_a.addListener(this, &ofApp::colorChangedHSB);

    parent.removeListener(this, &ofApp::parentChanged);
    parent.setBackgroundColor(baseLabelColor);
    guiInspector.add(parent.setup(parentText, scene.getSelectedGameObjectParentID(), 0, object_buttons.size()));
    parent.addListener(this, &ofApp::parentChanged);

    guiInspector.setPosition(ofGetWidth() - guiInspector.getWidth() - 2, 2);

    guiIsSetup = true;
}

void ofApp::updateGUIInspector(size_t buttonID)
{
    object_buttons.at(scene.getSelectedGameObjectID())->setBackgroundColor(baseButtonColor);
    scene.setSelectedGameObject(buttonID);

    //INSPECTOR
    object_buttons.at(buttonID)->setBackgroundColor(highlightedButtonColor);

    positionFields.disableEvents();
    positionFields = scene.getPositionSelectedGameObject();
    positionFields.enableEvents();

    rotation.disableEvents();
    rotation = scene.getEulerRotationSelectedGameObject();
    rotation.enableEvents();

    scaleFields.disableEvents();
    scaleFields = scene.getScaleSelectedGameObject();
    scaleFields.enableEvents();

    removeRGBListeners();
    ofColor selectedGameObjectColor = scene.getColorSelectedGameObject();
    RGB_r = selectedGameObjectColor.r;
    RGB_g = selectedGameObjectColor.g;
    RGB_b = selectedGameObjectColor.b;
    RGB_a = selectedGameObjectColor.a;
    addRGBListeners();

    removeHSBListeners();
    HSB_h = selectedGameObjectColor.getHue();
    HSB_s = selectedGameObjectColor.getSaturation();
    HSB_b = selectedGameObjectColor.getBrightness();
    HSB_a = selectedGameObjectColor.a;
    addHSBListeners();

    parent.removeListener(this, &ofApp::parentChanged);
    parent = scene.getSelectedGameObjectParentID();
    parent.addListener(this, &ofApp::parentChanged);
}

void ofApp::exit()
{}

void ofApp::parentChanged(int & newParentID)
{
    if (newParentID - 1 == scene.getSelectedGameObjectID())
    {
        cout << exceptionParentItself << endl;
    }
    else if (scene.isNewParentIDInSelectedGameObjectChildren(newParentID))
    {
        cout << exceptionChildParent << endl;
    }
    else
    {
        scene.setSelectedGameObjectParent(newParentID);
    }
}

void ofApp::addRGBListeners()
{
    RGB_r.addListener(this, &ofApp::colorChangedRGB);
    RGB_g.addListener(this, &ofApp::colorChangedRGB);
    RGB_b.addListener(this, &ofApp::colorChangedRGB);
    RGB_a.addListener(this, &ofApp::colorChangedRGB);
}

void ofApp::addHSBListeners()
{
    HSB_h.addListener(this, &ofApp::colorChangedHSB);
    HSB_s.addListener(this, &ofApp::colorChangedHSB);
    HSB_b.addListener(this, &ofApp::colorChangedHSB);
    HSB_a.addListener(this, &ofApp::colorChangedHSB);
}

void ofApp::removeRGBListeners()
{
    RGB_r.removeListener(this, &ofApp::colorChangedRGB);
    RGB_g.removeListener(this, &ofApp::colorChangedRGB);
    RGB_b.removeListener(this, &ofApp::colorChangedRGB);
    RGB_a.removeListener(this, &ofApp::colorChangedRGB);
}

void ofApp::removeHSBListeners()
{
    HSB_h.removeListener(this, &ofApp::colorChangedHSB);
    HSB_s.removeListener(this, &ofApp::colorChangedHSB);
    HSB_b.removeListener(this, &ofApp::colorChangedHSB);
    HSB_a.removeListener(this, &ofApp::colorChangedHSB);
}

void ofApp::colorChangedRGB(int & value)
{
    scene.setColorSelectedGameObject(ofColor(RGB_r, RGB_g, RGB_b, RGB_a));

    removeHSBListeners();

    ofColor currentColor = scene.getColorSelectedGameObject();
    HSB_h = currentColor.getHue();
    HSB_s = currentColor.getSaturation();
    HSB_b = currentColor.getBrightness();
    HSB_a = currentColor.a;

    addHSBListeners();
}

void ofApp::colorChangedHSB(int & value)
{
    ofColor newColor = ofColor(0);
    newColor.setHsb(HSB_h, HSB_s, HSB_b, HSB_a);
    scene.setColorSelectedGameObject(newColor);

    removeRGBListeners();

    ofColor currentColor = scene.getColorSelectedGameObject();
    RGB_r = currentColor.r;
    RGB_g = currentColor.g;
    RGB_b = currentColor.b;
    RGB_a = currentColor.a;

    addRGBListeners();
}

void ofApp::update()
{
    checkIfAButtonIsPressed();
    scene.update();
}

void ofApp::checkIfAButtonIsPressed()
{
    for (size_t i = 0; i < object_buttons.size(); i++)
    {
        if (*object_buttons[i])
        {
            if (scene.getSelectedGameObjectID() != i)
            {
                updateGUIInspector(i);
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

    if (GUIIsDisplayed)
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
        GUIIsDisplayed = !GUIIsDisplayed;
        break;
    case '1':
        addNewGameObject(0);
        break;
    case '2':
        addNewGameObject(1);
        break;
    case '3':
        addNewGameObject(2);
        break;
    case '4':
        addNewGameObject(3);
        break;
    case '5':
        addNewGameObject(4);
        break;
    case '6':
        addNewGameObject(5);
        break;
    case '7':
        addNewGameObject(6);
        break;
    default:
        break;
    }
}

void ofApp::addNewGameObject(size_t shapeType)
{
    ofxButton *object_button = new ofxButton();
    object_buttons.push_back(object_button);
    string shapeName;
    GameObject *gameObject;
    if (shapeType == Shape_Sphere)
    {
        gameObject = new Sphere();
        shapeName = sphereText;
    }
    else if (shapeType == Shape_Cube)
    {
        gameObject = new Cube();
        shapeName = cubeText;
    }
    else if (shapeType == Shape_Point) {
        gameObject = new Point();
        shapeName = pointText;
    }
    else if (shapeType == Shape_Line) {
        gameObject = new Line();
        shapeName = lineText;
    }
    else if (shapeType == Shape_Triangle) {
        gameObject = new Triangle();
        shapeName = triangleText;
    }
    else if (shapeType == Shape_Rectangle) {
        gameObject = new Rektangle();
        shapeName = rectangleText;
    }
    else if (shapeType == Shape_Polygon) {
        gameObject = new Polygone();
        shapeName = polygonText;
    }
    guiScene.add(object_button->setup(ofParameter<string>(shapeName)));
    scene.addGameObject(gameObject);
    if (guiIsSetup)
    {
        updateGUIInspector(object_buttons.size() - 1);
    }
    else
    {
        setupGUIInspector(object_buttons.size() - 1);
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

ofApp::~ofApp()
{
    for (ofxButton* button : object_buttons)
    {
        delete button;
    }
    object_buttons.clear();
}
