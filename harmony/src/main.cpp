#include "ofMain.h"
#include "ofApp.h"

int main()
{
    ofGLFWWindowSettings settings;
    settings.setGLVersion(3, 3);
    settings.width = 1024;
    settings.height = 768;
    ofCreateWindow(settings);
    ofRunApp(new ofApp());
}
