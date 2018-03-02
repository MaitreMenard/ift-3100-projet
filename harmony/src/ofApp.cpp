#include "ofApp.h"

//TODO: transfert all the rendering details into an AppRenderer class

void ofApp::setup()
{
    shiftIsPressed = false;

    ofSetFrameRate(60);
    ofEnableDepthTest();

    camera.setNearClip(0.1);

    scene.setup();

    Cube* cube = new Cube();
    scene.addGameObject(cube);
}

void ofApp::update()
{
    scene.update();
}

void ofApp::draw()
{
    ofClear(0);

    camera.setPosition(0, 0, 5);

    camera.begin();
    scene.draw();
    camera.end();
}

void ofApp::keyPressed(int key)
{
    switch (key)
    {
    case '+':
        if (shiftIsPressed)
        {
            scene.rescaleSelectedGameObject(1.2, 1.2, 1.2);
        }
        else
        {
            scene.translateSelectedGameObject(0, 0, 1);
        }
        break;
    case '-':
        if (shiftIsPressed)
        {
            scene.rescaleSelectedGameObject(0.8, 0.8, 0.8);
        }
        else
        {
            scene.translateSelectedGameObject(0, 0, -1);
        }
        break;
    case 356:   // left arrow
        scene.translateSelectedGameObject(-1, 0, 0);
        break;
    case 357:   // up arrow
        scene.translateSelectedGameObject(0, -1, 0);
        break;
    case 358:   // right arrow
        scene.translateSelectedGameObject(1, 0, 0);
        break;
    case 359:   // down arrow
        scene.translateSelectedGameObject(0, 1, 0);
        break;
    case 2304:  // shift
        shiftIsPressed = true;
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
