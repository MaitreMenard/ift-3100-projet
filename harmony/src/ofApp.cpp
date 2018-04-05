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

    gameObjectSelector.setup();
    gameObjectSelector.addListener(this, &ofApp::onSelectedGameObjectChange);

    textureSelector.setup();
    textureSelector.addListener(this, &ofApp::onSelectedGameObjectTextureChange);

    GUIIsDisplayed = true;
}

void ofApp::setupCamera()
{
    camera.setNearClip(0.1f);
    camera.setPosition(0, 2, 5);
}

void ofApp::setupInspector()
{
    inspector.setup(scene);

    inspector.positionFields.addListener(this, &ofApp::onSelectedGameObjectPositionChange);
    inspector.rotation.addListener(this, &ofApp::onSelectedGameObjectRotationChange);
    inspector.scaleFields.addListener(this, &ofApp::onSelectedGameObjectScaleChange);
    inspector.colorPicker.addListener(this, &ofApp::onSelectedGameObjectColorChange);
    inspector.parentField.addListener(this, &ofApp::onParentChanged);

    guiIsSetup = true;
}

void ofApp::exit()
{}

void ofApp::update()
{
    gameObjectSelector.update();
    textureSelector.update();
    scene.update();
}

void ofApp::onSelectedGameObjectChange(size_t& selectedGameObjectID)
{
    if (scene.getSelectedGameObjectID() != selectedGameObjectID)
    {
        scene.setSelectedGameObject(selectedGameObjectID);
        inspector.update(scene);
        textureSelector.setSelectedItem(scene.getSelectedGameObjectTextureID());
    }
}

void ofApp::onSelectedGameObjectTextureChange(size_t& selectedTextureID)
{
    if (scene.getSelectedGameObjectTextureID() != selectedTextureID)
    {
        scene.setSelectedGameObjectTexture(selectedTextureID);
    }
}

void ofApp::onSelectedGameObjectPositionChange(ofVec3f& newPosition)
{
    scene.setPositionSelectedGameObject(newPosition);
}

void ofApp::onSelectedGameObjectRotationChange(ofVec3f & newRotation)
{
    scene.setRotationSelectedGameObject(newRotation);
}

void ofApp::onSelectedGameObjectScaleChange(ofVec3f& newScale)
{
    scene.setScaleSelectedGameObject(newScale);
}

void ofApp::onSelectedGameObjectColorChange(ofColor & newColor)
{
    scene.setColorSelectedGameObject(newColor);
}

void ofApp::onParentChanged(int & newParentID)
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
        inspector.draw();
        gameObjectSelector.draw();
        if (scene.isSelectedGameObject2D())
        {
            textureSelector.draw();
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
        gameObjectSelector.setSelectedItem(scene.getSelectedGameObjectID());
        inspector.update(scene);
        textureSelector.setSelectedItem(scene.getSelectedGameObjectTextureID());
        break;
    case 8592: // CTRL_R + Y
    case 25: // CTRL_L + Y
        scene.redo();
        gameObjectSelector.setSelectedItem(scene.getSelectedGameObjectID());
        inspector.update(scene);
        textureSelector.setSelectedItem(scene.getSelectedGameObjectTextureID());
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
    gameObjectSelector.addItem(shapeName);
    scene.addGameObject(gameObject);
    size_t selectedGameObjectID = scene.getNumberOfGameObjects() - 1;
    gameObjectSelector.setSelectedItem(selectedGameObjectID);
    scene.setSelectedGameObject(selectedGameObjectID);
    if (guiIsSetup)
    {
        inspector.update(scene);
    }
    else
    {
        setupInspector();
    }
    textureSelector.setSelectedItem(scene.getSelectedGameObjectTextureID());
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
