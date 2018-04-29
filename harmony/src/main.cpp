#include "ofMain.h"
#include "ofApp.h"

int main()
{
    ofGLFWWindowSettings settings;
    settings.setGLVersion(3, 2);
    settings.width = 1024;
    settings.height = 768;
    settings.resizable = false;
    ofCreateWindow(settings);
    ofRunApp(new ofApp());


    /*ofSetupOpenGL(1024, 768, OF_WINDOW);

    ofRunApp(new ofApp());*/
}
