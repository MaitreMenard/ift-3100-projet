#include "ofApp.h"

void ofApp::setup()
{
    scene.enableUndoRedo();
    shiftIsPressed = false;
    CtrlIsPressed = false;

    ofSetFrameRate(60);
    ofEnableDepthTest();
    ofDisableArbTex();
    ofEnableAlphaBlending();

    setupCamera();
    gridPlane.setup();
    scene.setup();
    //Model3D* falcon = new Model3D("/models/millenium-falcon/millenium-falcon.obj",
    //    ofVec3f(-0.59, 0.17, 19.0),
    //    180,
    //    ofVec3f(0, 0, 1),
    //    ofVec3f(0.01, 0.01, 0.01));
    //scene.addGameObject(falcon);
    //Model3D* xWing = new Model3D("/models/xwing/x-wing.obj",
    //    ofVec3f(-14.59, 0.17, 19.0),
    //    180, ofVec3f(0, 0, 1),
    //    ofVec3f(0.01, 0.01, 0.01));
    //scene.addGameObject(xWing);

    ofSetVerticalSync(true);

    inspector_label.setBackgroundColor(headerLabelColor);
    scene_label.setBackgroundColor(headerLabelColor);
    texture_label.setBackgroundColor(headerLabelColor);

    guiScene.setup();
    guiScene.add(scene_label.setup(ofParameter<string>(sceneText)));

    GUIIsDisplayed = true;
}

void ofApp::setupGUIInspector(size_t buttonID)
{
    object_buttons.at(scene.getSelectedGameObjectID())->setBackgroundColor(baseButtonColor);
    scene.setSelectedGameObject(buttonID);

    object_buttons.at(buttonID)->setBackgroundColor(highlightedButtonColor);

    guiInspector.clear();
    guiInspector.setup();

    guiInspector.add(inspector_label.setup(ofParameter<string>(inspectorText)));

    guiInspector.add(positionFields.setup(positionText, scene.getPositionSelectedGameObject(),
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

    guiInspector.add(scaleFields.setup(scaleText, scene.getScaleSelectedGameObject(),
        ofVec3f(SCALE_MIN_VALUE), ofVec3f(SCALE_MAX_VALUE)));
    std::function<void(ofVec3f)> scaleListener = [=](ofVec3f value)
    {
        scene.setScaleSelectedGameObject(value.x, value.y, value.z);
    };
    scaleFields.addListener(scaleListener);

    rgb_label.setBackgroundColor(baseLabelColor);
    removeRGBListeners();
    guiInspector.add(rgb_label.setup(ofParameter<string>(rgbText)));
    ofColor selectedGameObjectColor = scene.getColorSelectedGameObject();
    guiInspector.add(RGB_r.setup(rText, selectedGameObjectColor.r, 0, 255));
    guiInspector.add(RGB_g.setup(gText, selectedGameObjectColor.g, 0, 255));
    guiInspector.add(RGB_b.setup(bText, selectedGameObjectColor.b, 0, 255));
    guiInspector.add(RGB_a.setup(aText, selectedGameObjectColor.a, 0, 255));
    addRGBListeners();

    hsb_label.setBackgroundColor(baseLabelColor);
    removeHSBListeners();
    guiInspector.add(hsb_label.setup(ofParameter<string>(hsbText)));
    guiInspector.add(HSB_h.setup(hText, selectedGameObjectColor.getHue(), 0, 255));
    guiInspector.add(HSB_s.setup(sText, selectedGameObjectColor.getSaturation(), 0, 255));
    guiInspector.add(HSB_b.setup(bText, selectedGameObjectColor.getBrightness(), 0, 255));
    guiInspector.add(HSB_a.setup(aText, selectedGameObjectColor.a, 0, 255));
    addHSBListeners();

    parent.removeListener(this, &ofApp::parentChanged);
    parent.setBackgroundColor(baseLabelColor);
    guiInspector.add(parent.setup(parentText, scene.getSelectedGameObjectParentID(), 0, object_buttons.size()));
    parent.addListener(this, &ofApp::parentChanged);

    guiInspector.setPosition(ofGetWidth() - guiInspector.getWidth() - 2, 2);

    guiIsSetup = true;

    if (scene.isSelectedGameObject2D())
    {
        setupGUITexture(0);//TODO: take actual texture
    }
    else
    {
        guiTexture.clear();
    }
}

void ofApp::updateGUIInspector(size_t buttonID)
{
    object_buttons.at(scene.getSelectedGameObjectID())->setBackgroundColor(baseButtonColor);
    scene.setSelectedGameObject(buttonID);

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
    parent.setMax(object_buttons.size());
    parent = scene.getSelectedGameObjectParentID();
    parent.addListener(this, &ofApp::parentChanged);

    if (scene.isSelectedGameObject2D())
    {
        setupGUITexture(0);//TODO: take actual texture
    }
    else
    {
        guiTexture.clear();
    }
}

void ofApp::setupGUITexture(size_t textureID)
{
    if (texture_buttons.empty())
    {
        texture_buttons.push_back(none_button);
        texture_buttons.push_back(cloud_button);
        texture_buttons.push_back(marble_button);
        texture_buttons.push_back(noise_button);
        texture_buttons.push_back(turbulence_button);
        texture_buttons.push_back(zoom_button);
    }

    guiTexture.clear();
    guiTexture.setup();

    guiTexture.add(texture_label.setup(ofParameter<string>(textureText)));

    none_button.setBackgroundColor(baseButtonColor);
    cloud_button.setBackgroundColor(baseButtonColor);
    marble_button.setBackgroundColor(baseButtonColor);
    noise_button.setBackgroundColor(baseButtonColor);
    turbulence_button.setBackgroundColor(baseButtonColor);
    zoom_button.setBackgroundColor(baseButtonColor);

    scene.setSelectedGameObjectTexture(textureID);
    texture_buttons.at(textureID).setBackgroundColor(highlightedButtonColor);

    guiTexture.add(none_button.setup(ofParameter<string>(noneText)));
    guiTexture.add(cloud_button.setup(ofParameter<string>(cloudText)));
    guiTexture.add(marble_button.setup(ofParameter<string>(marbleText)));
    guiTexture.add(noise_button.setup(ofParameter<string>(noiseText)));
    guiTexture.add(turbulence_button.setup(ofParameter<string>(turbulenceText)));
    guiTexture.add(zoom_button.setup(ofParameter<string>(zoomText)));

    guiTexture.setPosition(2, ofGetHeight() - guiTexture.getHeight() - 2);
}

void ofApp::updateGUITexture(size_t textureID)
{
    none_button.setBackgroundColor(baseButtonColor);
    cloud_button.setBackgroundColor(baseButtonColor);
    marble_button.setBackgroundColor(baseButtonColor);
    noise_button.setBackgroundColor(baseButtonColor);
    turbulence_button.setBackgroundColor(baseButtonColor);
    zoom_button.setBackgroundColor(baseButtonColor);

    scene.setSelectedGameObjectTexture(textureID);
    texture_buttons.at(textureID).setBackgroundColor(highlightedButtonColor);
}

void ofApp::exit()
{}

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

void ofApp::setupCamera()
{
    camera.setNearClip(0.1f);
    camera.setPosition(0, 2, 5);
}

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
        ofLog() << "mopdifying parent hierarchy";
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

void ofApp::update()
{
    checkIfATextureButtonIsPressed();
    checkIfASceneButtonIsPressed();
    scene.update();
}

void ofApp::checkIfATextureButtonIsPressed()
{
    for (size_t i = 0; i < texture_buttons.size(); i++)
    {
        if (texture_buttons[i])
        {
            if (scene.getSelectedGameObjectTextureID() != i)
            {
                updateGUITexture(i);
            }
            break;
        }
    }
}

void ofApp::checkIfASceneButtonIsPressed()
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
        if (scene.isSelectedGameObject2D())
        {
            guiTexture.draw();
        }
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
    case -1: // CTRL_R + Z
    case 26: // CTRL_L + Z
        scene.undo();
        break;
    case 8592: // CTRL_R + Y
    case 25: // CTRL_L + Y
        scene.redo();
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
    case 768: // Ctrl L and R
        CtrlIsPressed = true;
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
    case '8':
        addNewGameObject(Shape_Arrow);
        break;
    case '9':
        addNewGameObject(Shape_Star);
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
    guiTexture.clear();

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
    else if (shapeType == Shape_Point)
    {
        gameObject = new Point();
        shapeName = pointText;
    }
    else if (shapeType == Shape_Line)
    {
        gameObject = new Line();
        shapeName = lineText;
    }
    else if (shapeType == Shape_Triangle)
    {
        gameObject = new Triangle();
        shapeName = triangleText;
    }
    else if (shapeType == Shape_Rectangle)
    {
        gameObject = new Rektangle();
        shapeName = rectangleText;
    }
    else if (shapeType == Shape_Polygon)
    {
        gameObject = new Polygone();
        shapeName = polygonText;
    }
    else if (shapeType == Shape_Arrow)
    {
        gameObject = new Arrow();
        shapeName = arrowText;
    }
    else if (shapeType == Shape_Star)
    {
        gameObject = new Star();
        shapeName = starText;
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
    case 769: // Ctrl L and R
    case 770:
        CtrlIsPressed = false;
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
