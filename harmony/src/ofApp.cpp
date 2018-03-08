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

	gridPlane.setup();
	scene.setup();

	Cube* cube = new Cube();
	scene.addGameObject(cube);

	ofSetVerticalSync(true);

	gui.setup();

	scale_label.setBackgroundColor(ofColor(48, 48, 72));
	gui.add(scale_label.setup(ofParameter<string>("Scale")));
	scale_x.addListener(this, &ofApp::xScaleChanged);
	scale_y.addListener(this, &ofApp::yScaleChanged);
	scale_z.addListener(this, &ofApp::zScaleChanged);
	gui.add(scale_x.setup("X: ", "1"));
	gui.add(scale_y.setup("Y: ", "1"));
	gui.add(scale_z.setup("Z: ", "1"));

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

	colorType.addListener(this, &ofApp::colorTypeChanged);
	colorType.setBackgroundColor(ofColor(48, 48, 72));
	gui.add(colorType.setup("HSB", true));

	color.setHeaderBackgroundColor(ofColor(48, 48, 72));
	gui.add(color.setup("Color", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));

	gui.setPosition(ofGetWidth() - gui.getWidth() - 2, 2);

	bHide = false;
}

void ofApp::exit()
{}

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

void ofApp::colorTypeChanged(bool & pressed)
{
	if (pressed) {
		colorType.setName("RGB");
		//TODO: Change color into RGB
	}
	else {
		colorType.setName("HSB");
		//TODO: Change color into HSB
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

	camera.setPosition(0, 2, 5);
	camera.lookAt(ofVec3f(0, 0, 0));

	camera.begin();
	scene.draw();
	gridPlane.draw();
	camera.end();

	ofSetColor(color);

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

void ofApp::updateUIValues(ofxInputField<string> & field, int & key) {
	
}

void ofApp::keyPressed(int key)
{
	switch (key)
	{
	case ' ':
		takeScreenShot();
		break;
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
	case 'w':   // x, towards back
		scene.rotateSelectedGameObject(10, -1, 0, 0);
		break;
	case 's':   // x, towards camera
		scene.rotateSelectedGameObject(10, 1, 0, 0);
		break;
	case 'e':   // y, left
		scene.rotateSelectedGameObject(10, 0, -1, 0);
		break;
	case 'd':   // y, right
		scene.rotateSelectedGameObject(10, 0, 1, 0);
		break;
	case 'r':   // z, clockwise
		scene.rotateSelectedGameObject(10, 0, 0, -1);
		break;
	case 'f':   // z, anticlockwise
		scene.rotateSelectedGameObject(10, 0, 0, 1);
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
