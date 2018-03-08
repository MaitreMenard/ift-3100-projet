#include "ofApp.h"

//TODO: transfer all the rendering details into an AppRenderer class

void ofApp::setup()
{
	shiftIsPressed = false;

	ofSetFrameRate(60);
	//ofEnableDepthTest();

	camera.setNearClip(0.1f);

	scene.setup();

	Cube* cube = new Cube();
	scene.addGameObject(cube);

	ofSetVerticalSync(true);

	// we add this listener before setting up so the initial circle resolution is correct
	//circleResolution.addListener(this, &ofApp::circleResolutionChanged);

	//gui.setup(); // most of the time you don't need a name
	//gui.add(filled.setup("fill", true));
	//gui.add(radius.setup("radius", 140, 10, 300));
	//gui.add(center.setup("center", ofVec2f(ofGetWidth()*.5, ofGetHeight()*.5), ofVec2f(0, 0), ofVec2f(ofGetWidth(), ofGetHeight())));
	//gui.add(color.setup("color", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
	//gui.add(circleResolution.setup("circle res", 5, 3, 90));
	//gui.add(twoCircles.setup("two circles"));
	//gui.add(textField.setup("textfield:", "type sth. here"));

	gui.setup();
	scale_label.setBackgroundColor(ofColor(80, 80, 80));
	gui.add(scale_label.setup(ofParameter<string>("Scale")));
	gui.add(scale_x.setup("X: ", 50, 0, 100));
	gui.add(scale_y.setup("Y: ", 50, 0, 100));
	gui.add(scale_z.setup("Z: ", 50, 0, 100));
	position_label.setBackgroundColor(ofColor(80, 80, 80));
	gui.add(position_label.setup(ofParameter<string>("Position")));
	gui.add(position_x.setup("X: ", 0, FLT_MIN, FLT_MAX));
	gui.add(position_y.setup("Y: ", 0, FLT_MIN, FLT_MAX));
	gui.add(position_z.setup("Z: ", 0, FLT_MIN, FLT_MAX));
	gui.add(rotation.setup("Rotation", ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), ofVec3f(360, 360, 360)));
	colorType.addListener(this, &ofApp::colorTypeChanged);
	gui.add(colorType.setup("HSB", true));
	gui.add(color.setup("Color", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
	gui.setPosition(ofGetWidth() - gui.getWidth() - 2, 2);

	bHide = false;
}

void ofApp::exit()
{}

void ofApp::colorTypeChanged(bool & pressed)
{
	if (colorType.getName() == "RGB") {
		colorType.setName("HSB");
		//TODO: Change color into HSB
	}
	else {
		colorType.setName("RGB");
		//TODO: Change color into RGB
	}
}

void ofApp::update()
{
    scene.update();
}

void ofApp::draw()
{
    ofClear(0);

	ofBackgroundGradient(ofColor::white, ofColor::gray); //CHANGE LA COULEUR DU FOND D'ECRAN

    camera.setPosition(0, 0, 5);

    camera.begin();
    scene.draw();
    camera.end();

	/*if (filled)
	{
		ofFill();
	}
	else
	{
		ofNoFill();
	}*/

	ofSetColor(color);
	/*if (twoCircles)
	{
		ofDrawCircle(center->x - radius*.5, center->y, radius);
		ofDrawCircle(center->x + radius*.5, center->y, radius);
	}
	else
	{
		ofDrawCircle((ofVec2f)center, radius);
	}*/

	if (!bHide)
	{
		gui.draw();
	}
}

void ofApp::keyPressed(int key)
{
    switch (key)
    {
    case '+':
        if (shiftIsPressed)
        {
            scene.rescaleSelectedGameObject(1.2f, 1.2f, 1.2f);
        }
        else
        {
            scene.translateSelectedGameObject(0, 0, 1);
        }
        break;
    case '-':
        if (shiftIsPressed)
        {
            scene.rescaleSelectedGameObject(0.8f, 0.8f, 0.8f);
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
        scene.translateSelectedGameObject(0, 1, 0);
        break;
    case 358:   // right arrow
        scene.translateSelectedGameObject(1, 0, 0);
        break;
    case 359:   // down arrow
        scene.translateSelectedGameObject(0, -1, 0);
        break;
	case 119:   // w
		scene.rotateSelectedGameObject(-1, 0, 0);
		break;
	case 97:   // a
		scene.rotateSelectedGameObject(0, 1, 0);
		break;
	case 115:   // s
		scene.rotateSelectedGameObject(1, 0, 0);
		break;
	case 100:   // d
		scene.rotateSelectedGameObject(0, -1, 0);
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
