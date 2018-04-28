#include "ofMain.h"
#include "ofApp.h"

int main()
{
    /*ofSetupOpenGL(1024, 768, OF_WINDOW);

    ofRunApp(new ofApp());*/
    ofGLFWWindowSettings settings;
    settings.setGLVersion(3, 3);
    settings.width = 1024;
    settings.height = 768;
    ofCreateWindow(settings);
    ofRunApp(new ofApp());
}
