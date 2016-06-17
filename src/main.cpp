#include "ofMain.h"
#include "ofApp.h"

int main()
{
    ofGLWindowSettings settings;
    settings.width = 1920;
    settings.height = 1080;
    settings.windowMode = OF_WINDOW;
//    settings.setGLVersion(2,1);
    settings.setGLVersion(3,2);
    ofCreateWindow(settings);
	ofRunApp(new ofApp());
}
