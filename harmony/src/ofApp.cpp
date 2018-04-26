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

    setupInspector();

    gameObjectSelector.setup();
    gameObjectSelector.addListener(this, &ofApp::onSelectedGameObjectChange);
    gameObjectSelector.addControlPointListener(this, &ofApp::onSelectedControlPointChange);

    textureSelector.setup(textureFactory);
    textureSelector.addListener(this, &ofApp::onSelectedGameObjectTextureChange);

    light = new Light(lightText);
    light->setLightMode(Point);
    /*light2 = new Light(lightText);
    light2->setLightMode(Spot);
    light3 = new Light(lightText);
    light3->setLightMode(Directional);
    light4 = new Light(lightText);
    light4->setLightMode(Point);*/
    setupNewGameObject(light);
    /*setupNewGameObject(light2);
    setupNewGameObject(light3);
    setupNewGameObject(light4);*/

    lightIsActive = true;
    setupLight(lightIsActive);

    GUIIsDisplayed = true;
}

void ofApp::setupCamera()
{
    camera.setNearClip(0.1f);
    camera.setPosition(initialCameraPosition);

    cameraPortal.setNearClip(0.1f);
    cameraPortal.setOrientation(ofVec3f(0, -180, 90));
}

void ofApp::setupInspector()
{
    inspector.setup();

    inspector.positionFields.addListener(this, &ofApp::onSelectedGameObjectPositionChange);
    inspector.rotation.addListener(this, &ofApp::onSelectedGameObjectRotationChange);
    inspector.scaleFields.addListener(this, &ofApp::onSelectedGameObjectScaleChange);
    inspector.colorPicker.addListener(this, &ofApp::onSelectedGameObjectColorChange);
    inspector.diffuseColorpicker.addListener(this, &ofApp::onSelectedGameObjectDiffuseColorChange);
    inspector.specularColorPicker.addListener(this, &ofApp::onSelectedGameObjectSpecularColorChange);
    inspector.ambientColorPicker.addListener(this, &ofApp::onSelectedGameObjectAmbientColorChange);
    inspector.parentField.addListener(this, &ofApp::onParentChanged);
    inspector.addControlPointButton.addListener(this, &ofApp::onSelectedCurveAddControlPoint);
}

void ofApp::setupLight(bool enableOrDisable)
{
    lightIsActive = enableOrDisable;
    if (lightIsActive)
    {
        ofEnableLighting();
    }
    else
    {
        ofDisableLighting();
    }
}

void ofApp::exit()
{}

void ofApp::update()
{
    gameObjectSelector.update();
    textureSelector.update();
    scene.update();
}

void ofApp::onSelectedGameObjectChange(GameObject*& selectedGameObject)
{
    setSelectedGameObject(selectedGameObject);
}

void ofApp::setSelectedGameObject(GameObject* selectedGameObject)
{
    if (scene.getSelectedGameObject() != selectedGameObject)
    {
        scene.setSelectedGameObject(selectedGameObject);
        inspector.update(scene);
        if (selectedGameObject->is2D())
        {
            textureSelector.setSelectedItem(scene.getSelectedGameObjectTexture());
        }
    }
}

void ofApp::onSelectedControlPointChange(ControlPoint*& controlPoint)
{
    setSelectedGameObject(controlPoint);
    controlPoint->getCurve()->setSelected(true);
}

void ofApp::onSelectedGameObjectTextureChange(Texture*& texture)
{
    if (scene.getSelectedGameObjectTexture() != texture)
    {
        scene.setSelectedGameObjectTexture(texture);
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

void ofApp::onSelectedGameObjectDiffuseColorChange(ofColor & diffuseColor)
{
    scene.getSelectedGameObject()->setDiffuseColor(diffuseColor);
}

void ofApp::onSelectedGameObjectSpecularColorChange(ofColor & specularColor)
{
    scene.getSelectedGameObject()->setSpecularColor(specularColor);
}

void ofApp::onSelectedGameObjectAmbientColorChange(ofColor & ambientColor)
{
    scene.getSelectedGameObject()->setAmbientColor(ambientColor);
}

void ofApp::onParentChanged(int & newParentButtonID)
{
    if (newParentButtonID == 0)
    {
        scene.removeSelectedGameObjectParent();
    }
    else
    {
        GameObject* parentGameObject = scene.getGameObjectByIndex(newParentButtonID - 1);
        scene.setSelectedGameObjectParent(parentGameObject);
    }
}

void ofApp::onSelectedCurveAddControlPoint()
{
    BezierCurve* bezierCurve = (BezierCurve*)scene.getSelectedGameObject();
    ControlPoint* newControlPoint = bezierCurve->addControlPoint();
    gameObjectSelector.addControlPoint(bezierCurve, newControlPoint);
}

void ofApp::draw()
{
    ofClear(0);

    ofBackgroundGradient(ofColor::white, ofColor::gray);

    if (currentlyDrawingPortal1)
    {
        createPortal(1);
    }
    else if (currentlyDrawingPortal2)
    {
        createPortal(2);
    }
    else
    {
        ofPushMatrix();
        camera.begin();
        if (camera.getOrtho())
        {
            ofScale(ofVec3f(100));
        }
        if (lightIsActive)
        {
            light->enable();
            /*light2->enable();
            light3->enable();
            light4->enable();*/
        }
        scene.draw();
        gridPlane.draw();
        if (lightIsActive)
        {
            light->disable();
            /*light2->disable();
            light3->disable();
            light4->disable();*/
        }
        camera.end();
        ofPopMatrix();

        if (GUIIsDisplayed)
        {
            if (lightIsActive)
            {
                ofDisableLighting();
            }
            ofDisableDepthTest();
            inspector.draw();
            gameObjectSelector.draw();
            if (scene.isSelectedGameObject2D())
            {
                textureSelector.draw();
            }
            ofEnableDepthTest();
            if (lightIsActive)
            {
                ofEnableLighting();
            }
        }
    }
}

void ofApp::createPortal(size_t portalId)
{
    if (portalId == 1)
    {
        currentlyDrawingPortal1 = false;
        currentlyDrawingPortal2 = true;
        cameraPortal.setPosition(ofVec3f(-2, 2, 0));
    }
    else if (portalId == 2)
    {
        currentlyDrawingPortal2 = false;
        cameraPortal.setPosition(ofVec3f(2, 2, 0));
    }
    scene.setSelectedGameObject(nullptr);
    cameraPortal.begin();
    if (lightIsActive)
    {
        light->enable();
        /*light2->enable();
        light3->enable();
        light4->enable();*/
    }
    scene.draw();
    gridPlane.draw();
    if (lightIsActive)
    {
        light->disable();
        /*light2->disable();
        light3->disable();
        light4->disable();*/
    }
    cameraPortal.end();
    addNewGameObject(Shape_Portal, &Texture("portal", getCameraPortalImage()));
    scene.getSelectedGameObject()->setPosition(cameraPortal.getPosition());
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

ofPixels ofApp::getCameraPortalImage()
{
    ofImage image;
    image.grabScreen((ofGetWindowWidth() - ofGetWindowHeight()) / 2, 0, ofGetWindowHeight(), ofGetWindowHeight());

    return image.getPixels();
}

void ofApp::toggleGUIVisibility()
{
    GUIIsDisplayed = !GUIIsDisplayed;
}

void ofApp::keyPressed(int key)
{
    switch (key)
    {
    case -1: // CTRL_R + Z
    case 26: // CTRL_L + Z
        scene.undo();
        gameObjectSelector.setSelectedItem(scene.getSelectedGameObject());
        inspector.update(scene);
        textureSelector.setSelectedItem(scene.getSelectedGameObjectTexture());
        break;
    case 8592: // CTRL_R + Y
    case 25: // CTRL_L + Y
        scene.redo();
        gameObjectSelector.setSelectedItem(scene.getSelectedGameObject());
        inspector.update(scene);
        textureSelector.setSelectedItem(scene.getSelectedGameObjectTexture());
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
    case 'r':
        camera.setPosition(initialCameraPosition);
        camera.setOrientation(ofVec3f(0, 0, 0));
        break;
    case 'c':
        if (camera.getOrtho())
        {
            camera.disableOrtho();
        }
        else
        {
            camera.enableOrtho();
        }
        break;
    case 2304:  // shift
        shiftIsPressed = true;
        break;
    case 768: // Ctrl L and R
        CtrlIsPressed = true;
        break;
    case 'h':   //todo: make this some other key
        toggleGUIVisibility();
        break;
    case '1':
        addNewGameObject(Shape_Sphere, textureFactory.getEmptyTexture());
        break;
    case '2':
        addNewGameObject(Shape_Cube, textureFactory.getEmptyTexture());
        break;
    case '3':
        addNewGameObject(Shape_Line, textureFactory.getEmptyTexture());
        break;
    case '4':
        addNewGameObject(Shape_Triangle, textureFactory.getEmptyTexture());
        break;
    case '5':
        addNewGameObject(Shape_Rectangle, textureFactory.getEmptyTexture());
        break;
    case '6':
        addNewGameObject(Shape_Pentagon, textureFactory.getEmptyTexture());
        break;
    case '7':
        addNewGameObject(Shape_Circle, textureFactory.getEmptyTexture());
        break;
    case '8':
        addNewGameObject(Shape_Arrow, textureFactory.getEmptyTexture());
        break;
    case '9':
        addNewGameObject(Shape_Star, textureFactory.getEmptyTexture());
        break;
    case 'p':
        currentlyDrawingPortal1 = true;
        break;
    case 'm':
        addNewGameObject(Shape_Falcon, textureFactory.getEmptyTexture());
        break;
    case 'x':
        addNewGameObject(Shape_XWing, textureFactory.getEmptyTexture());
        break;
    case 'b':
        addNewGameObject(Shape_Bezier, textureFactory.getEmptyTexture());
        break;
    case 'n':   //todo: make this h
        addNewGameObject(Shape_Hermite, textureFactory.getEmptyTexture());
        break;
    default:
        break;
    }
}

void ofApp::addNewGameObject(size_t shapeType, Texture* texture)
{
    setupNewGameObject(gameobjectFactory.createNewGameObject(shapeType, texture));
}

void ofApp::setupNewGameObject(GameObject* gameObject)
{
    gameObject->accept(gameObjectSelector);
    scene.addGameObject(gameObject);
    gameObjectSelector.setSelectedItem(gameObject);
    scene.setSelectedGameObject(gameObject);
    inspector.update(scene);
    if (gameObject->is2D())
    {
        textureSelector.setSelectedItem(scene.getSelectedGameObjectTexture());
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
