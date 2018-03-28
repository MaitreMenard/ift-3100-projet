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

    ofSetVerticalSync(true);

    guiScene.setup();
    guiScene.setName(sceneText);
    guiScene.setHeaderBackgroundColor(headerLabelColor);

    for (int i = 0; i < textureTexts.size(); i++)
    {
        texture_buttons.push_back(new ofxButton());
    }

    GUIIsDisplayed = true;
}

void ofApp::setupGUIInspector(size_t buttonID)
{
    //FIXME: these 3 lines dont go in this method
    object_buttons.at(scene.getSelectedGameObjectID())->setBackgroundColor(baseButtonColor);
    scene.setSelectedGameObject(buttonID);
    object_buttons.at(buttonID)->setBackgroundColor(highlightedButtonColor);

    guiInspector.setup();
    guiInspector.setName(inspectorText);
    guiInspector.setHeaderBackgroundColor(headerLabelColor);

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

    ofColor selectedGameObjectColor = scene.getColorSelectedGameObject();
    guiInspector.add(colorPicker.setup(selectedGameObjectColor));
    std::function<void(ofColor)> colorListener = [=](ofColor color)
    {
        scene.setColorSelectedGameObject(color);
    };
    colorPicker.addListener(colorListener);

    parent.setBackgroundColor(baseLabelColor);
    guiInspector.add(parent.setup(parentText, scene.getSelectedGameObjectParentID(), 0, object_buttons.size()));
    parent.addListener(this, &ofApp::parentChanged);

    guiInspector.setPosition(ofGetWidth() - guiInspector.getWidth() - 2, 2);

    guiIsSetup = true;

    guiTexture.clear();
    if (scene.isSelectedGameObject2D())
    {
        setupGUITexture(scene.getSelectedGameObjectTextureID());
    }
}

void ofApp::updateGUIInspector(size_t buttonID)
{
    //FIXME: these 3 lines dont go in this method
    object_buttons.at(scene.getSelectedGameObjectID())->setBackgroundColor(baseButtonColor);
    scene.setSelectedGameObject(buttonID);
    object_buttons.at(buttonID)->setBackgroundColor(highlightedButtonColor);

    positionFields = scene.getPositionSelectedGameObject();
    rotation = scene.getEulerRotationSelectedGameObject();
    scaleFields = scene.getScaleSelectedGameObject();

    ofColor selectedGameObjectColor = scene.getColorSelectedGameObject();
    colorPicker.setColor(selectedGameObjectColor);

    parent.removeListener(this, &ofApp::parentChanged);
    parent.setMax(object_buttons.size());
    parent = scene.getSelectedGameObjectParentID();
    parent.addListener(this, &ofApp::parentChanged);

    guiTexture.clear();
    if (scene.isSelectedGameObject2D())
    {
        setupGUITexture(scene.getSelectedGameObjectTextureID());
    }
}

void ofApp::setupGUITexture(size_t textureID)
{
    guiTexture.setup();
    guiTexture.setName(textureText);
    guiTexture.setHeaderBackgroundColor(headerLabelColor);

    for (int i = 0; i < textureTexts.size(); i++)
    {
        texture_buttons.at(i)->setBackgroundColor(baseButtonColor);
        guiTexture.add(texture_buttons.at(i)->setup(ofParameter<string>(textureTexts.at(i))));
    }

    texture_buttons.at(textureID)->setBackgroundColor(highlightedButtonColor);

    guiTexture.setPosition(2, ofGetHeight() - guiTexture.getHeight() - 2);
}

void ofApp::updateGUITexture(size_t textureID)
{
    for (int i = 0; i < textureTexts.size(); i++)
    {
        texture_buttons.at(i)->setBackgroundColor(baseButtonColor);
    }

    scene.setSelectedGameObjectTexture(textureID);
    texture_buttons.at(textureID)->setBackgroundColor(highlightedButtonColor);
}

void ofApp::exit()
{}

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
        ofLog() << "Modifying parent hierarchy";
        scene.setSelectedGameObjectParent(newParentID);
    }
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
        if (*texture_buttons.at(i))
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
        updateGUIInspector(scene.getSelectedGameObjectID());
        break;
    case 8592: // CTRL_R + Y
    case 25: // CTRL_L + Y
        scene.redo();
        updateGUIInspector(scene.getSelectedGameObjectID());
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
        addNewGameObject(Shape_Sphere);
        break;
    case '2':
        addNewGameObject(Shape_Cube);
        break;
    case '3':
        addNewGameObject(Shape_Line);
        break;
    case '4':
        addNewGameObject(Shape_Triangle);
        break;
    case '5':
        addNewGameObject(Shape_Rectangle);
        break;
    case '6':
        addNewGameObject(Shape_Pentagon);
        break;
    case '7':
        addNewGameObject(Shape_Circle);
        break;
    case '8':
        addNewGameObject(Shape_Arrow);
        break;
    case '9':
        addNewGameObject(Shape_Star);
        break;
    case 'm':
        addNewGameObject(Shape_Falcon);
        break;
    case 'x':
        addNewGameObject(Shape_XWing);
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
    else if (shapeType == Shape_Pentagon)
    {
        gameObject = new Polygone(5);
        shapeName = pentagonText;
    }
    else if (shapeType == Shape_Circle)
    {
        gameObject = new Polygone(90);
        shapeName = circleText;
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
    else if (shapeType == Shape_Falcon)
    {
        gameObject = new Model3D("/models/millenium-falcon/millenium-falcon.obj",
            ofVec3f(-0.59, 0.17, 19.0),
            180,
            ofVec3f(0, 0, 1),
            ofVec3f(0.01, 0.01, 0.01));
        shapeName = falconText;
    }
    else if (shapeType == Shape_XWing)
    {
        gameObject = new Model3D("/models/xwing/x-wing.obj",
                ofVec3f(-14.59, 0.17, 19.0),
                180, ofVec3f(0, 0, 1),
                ofVec3f(0.01, 0.01, 0.01));
        shapeName = xwingText;
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
    for (ofxButton* button2 : texture_buttons)
    {
        delete button2;
    }
    object_buttons.clear();
    texture_buttons.clear();
}
