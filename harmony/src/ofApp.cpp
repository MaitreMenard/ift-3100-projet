#include "ofApp.h"

//TODO: transfer all the rendering details into an AppRenderer class

void ofApp::setup()
{
    shiftIsPressed = false;

    ofSetFrameRate(60);
    ofEnableDepthTest();
    ofDisableArbTex();
    ofEnableAlphaBlending();

    setupCamera();
    gridPlane.setup();
    scene.setup();

    Model3D* falcon = new Model3D("/models/millenium-falcon/millenium-falcon.obj",
        ofVec3f(-0.59, 0.17, 19.0),
        180,
        ofVec3f(0, 0, 1),
        ofVec3f(0.01, 0.01, 0.01));
    scene.addGameObject(falcon);
    //Model3D* xWing = new Model3D("/models/xwing/x-wing.obj",
    //    ofVec3f(-14.59, 0.17, 19.0),
    //    180, ofVec3f(0, 0, 1),
    //    ofVec3f(0.01, 0.01, 0.01));
    //scene.addGameObject(xWing);

    Sphere* sphere = new Sphere();
    plan2D* plan = new plan2D();

    //sphere->translate(0.0f, 2.0f, 0.0f);
    //scene.addGameObject(sphere);
    //scene.addGameObject(plan);

    // Test procedural texture
    //ofPixels * pix = new ofPixels();
    //pix->allocate(500, 500, OF_PIXELS_RGB);
    //scene.getGameObject(1)->setTexture(tFac.setMarbleTexture(pix, 5.0, 5.0, 1.0, 16.0));

    //Cube* cube = new Cube();
    //Cube* cube2 = new Cube();
    //cube->addChild(cube2);
    //cube2->reScale(0.5f, 0.5f, 0.5f);
    //cube2->translate(0.0f, 1.0f, 0.0f);
    //scene.addGameObject(cube);

    ofSetVerticalSync(true);

    gui.setup();

    position_label.setBackgroundColor(ofColor(48, 48, 72));
    gui.add(position_label.setup(ofParameter<string>("Position")));
    position_x.addListener(this, &ofApp::xPositionChanged);
    position_y.addListener(this, &ofApp::yPositionChanged);
    position_z.addListener(this, &ofApp::zPositionChanged);
    gui.add(position_x.setup("X: ", "0"));
    gui.add(position_y.setup("Y: ", "0"));
    gui.add(position_z.setup("Z: ", "0"));

    rotation.setHeaderBackgroundColor(ofColor(48, 48, 72));
    gui.add(rotation.setup("Rotation", ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), ofVec3f(360, 360, 360)));

    scale_label.setBackgroundColor(ofColor(48, 48, 72));
    gui.add(scale_label.setup(ofParameter<string>("Scale")));
    scale_x.addListener(this, &ofApp::xScaleChanged);
    scale_y.addListener(this, &ofApp::yScaleChanged);
    scale_z.addListener(this, &ofApp::zScaleChanged);
    gui.add(scale_x.setup("X: ", "1"));
    gui.add(scale_y.setup("Y: ", "1"));
    gui.add(scale_z.setup("Z: ", "1"));

    colorType.addListener(this, &ofApp::colorTypeChanged);
    colorType.setBackgroundColor(ofColor(48, 48, 72));
    gui.add(colorType.setup("HSB", true));

    color.setHeaderBackgroundColor(ofColor(48, 48, 72));
    gui.add(color.setup("Color", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));

    gui.setPosition(ofGetWidth() - gui.getWidth() - 2, 2);

    bHide = false;
}

void ofApp::setupCamera()
{
    camera.setNearClip(0.1f);
    camera.setPosition(0, 2, 5);
}

void ofApp::exit()
{}

void ofApp::xPositionChanged(string & value)
{
    float fValue;
    try
    {
        fValue = stof(value);
        if (fValue < POSITION_MIN_VALUE)
        {
            fValue = POSITION_MIN_VALUE;
        }
        else if (fValue > POSITION_MAX_VALUE)
        {
            fValue = POSITION_MAX_VALUE;
        }
        scene.setPositionSelectedGameObject(fValue, POSITION_MIN_VALUE - 1, POSITION_MIN_VALUE - 1);
    }
    catch (...)
    {
        cout << value << " is not a valid input (xPositionChanged)" << endl;
        scene.setPositionSelectedGameObject(0, POSITION_MIN_VALUE - 1, POSITION_MIN_VALUE - 1);
    }
}

void ofApp::yPositionChanged(string & value)
{
    float fValue;
    try
    {
        fValue = stof(value);
        if (fValue < POSITION_MIN_VALUE)
        {
            fValue = POSITION_MIN_VALUE;
        }
        else if (fValue > POSITION_MAX_VALUE)
        {
            fValue = POSITION_MAX_VALUE;
        }
        scene.setPositionSelectedGameObject(POSITION_MIN_VALUE - 1, fValue, POSITION_MIN_VALUE - 1);
    }
    catch (...)
    {
        cout << value << " is not a valid input (yPositionChanged)" << endl;
        scene.setPositionSelectedGameObject(POSITION_MIN_VALUE - 1, 0, POSITION_MIN_VALUE - 1);
    }
}

void ofApp::zPositionChanged(string & value)
{
    float fValue;
    try
    {
        fValue = stof(value);
        if (fValue < POSITION_MIN_VALUE)
        {
            fValue = POSITION_MIN_VALUE;
        }
        else if (fValue > POSITION_MAX_VALUE)
        {
            fValue = POSITION_MAX_VALUE;
        }
        scene.setPositionSelectedGameObject(POSITION_MIN_VALUE - 1, POSITION_MIN_VALUE - 1, fValue);
    }
    catch (...)
    {
        cout << value << " is not a valid input (zPositionChanged)" << endl;
        scene.setPositionSelectedGameObject(POSITION_MIN_VALUE - 1, POSITION_MIN_VALUE - 1, 0);
    }
}

void ofApp::xScaleChanged(string & value)
{
    float fValue;
    try
    {
        fValue = stof(value);
        if (fValue < SCALE_MIN_VALUE)
        {
            fValue = SCALE_MIN_VALUE;
        }
        else if (fValue > SCALE_MAX_VALUE)
        {
            fValue = SCALE_MAX_VALUE;
        }
        scene.setScaleSelectedGameObject(fValue, SCALE_MIN_VALUE - 1, SCALE_MIN_VALUE - 1);
    }
    catch (...)
    {
        cout << value << " is not a valid input (xScaleChanged)" << endl;
        scene.setScaleSelectedGameObject(1, SCALE_MIN_VALUE - 1, SCALE_MIN_VALUE - 1);
    }
}

void ofApp::yScaleChanged(string & value)
{
    float fValue;
    try
    {
        fValue = stof(value);
        if (fValue < SCALE_MIN_VALUE)
        {
            fValue = SCALE_MIN_VALUE;
        }
        else if (fValue > SCALE_MAX_VALUE)
        {
            fValue = SCALE_MAX_VALUE;
        }
        scene.setScaleSelectedGameObject(SCALE_MIN_VALUE - 1, fValue, SCALE_MIN_VALUE - 1);
    }
    catch (...)
    {
        cout << value << " is not a valid input (yScaleChanged)" << endl;
        scene.setScaleSelectedGameObject(SCALE_MIN_VALUE - 1, 1, SCALE_MIN_VALUE - 1);
    }
}

void ofApp::zScaleChanged(string & value)
{
    float fValue;
    try
    {
        fValue = stof(value);
        if (fValue < SCALE_MIN_VALUE)
        {
            fValue = SCALE_MIN_VALUE;
        }
        else if (fValue > SCALE_MAX_VALUE)
        {
            fValue = SCALE_MAX_VALUE;
        }
        scene.setScaleSelectedGameObject(SCALE_MIN_VALUE - 1, SCALE_MIN_VALUE - 1, fValue);
    }
    catch (...)
    {
        cout << value << " is not a valid input (zScaleChanged)" << endl;
        scene.setScaleSelectedGameObject(SCALE_MIN_VALUE - 1, SCALE_MIN_VALUE - 1, 1);
    }
}

void ofApp::colorTypeChanged(bool & pressed)
{
    if (pressed)
    {
        colorType.setName("RGB");
        //TODO: Change color into RGB
    }
    else
    {
        colorType.setName("HSB");
        //TODO: Change color into HSB
    }
}

void ofApp::update()
{
    scene.update();
    scene.updateSelectedGameObjectColor(color);
    scene.updateSelectedGameObjectRotation(rotation);
}

void ofApp::draw()
{
    ofClear(0);

    ofBackgroundGradient(ofColor::white, ofColor::gray); //CHANGE LA COULEUR DU FOND D'ECRAN

    //ofSetColor(color);

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

void ofApp::updateUIValues(ofxInputField<string> & field, int & key)
{

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
