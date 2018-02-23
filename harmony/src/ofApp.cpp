#include "ofApp.h"

//TODO: transfert all the rendering details into an AppRenderer class

void ofApp::setup()
{
    ofSetFrameRate(60);
    ofEnableDepthTest();

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
    ofPushMatrix();

    ofTranslate(ofGetWidth() / 2.0f, ofGetHeight() / 2.0f, 0);
    
    scene.draw();

    ofPopMatrix();
}

void ofApp::keyPressed(int key)
{
    switch (key)
    {
    case '+':
        scene.translateSelectedGameObject(0, 0, 20);
        break;
    case '-':
        scene.translateSelectedGameObject(0, 0, -20);
        break;
    case 356:   // left arrow
        scene.translateSelectedGameObject(-20, 0, 0);
        break;
    case 357:   // up arrow
        scene.translateSelectedGameObject(0, -20, 0);
        break;
    case 358:   // right arrow
        scene.translateSelectedGameObject(20, 0, 0);
        break;
    case 359:   // down arrow
        scene.translateSelectedGameObject(0, 20, 0);
        break;
    default:
        break;
    }
}

void ofApp::keyReleased(int key)
{

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
