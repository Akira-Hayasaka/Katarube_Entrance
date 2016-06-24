#include "ofMain.h"
#include "ofApp.h"
#include "Constants.h"

int main()
{
    ofGLWindowSettings settings;
	settings.width = APP_W;
    settings.height = APP_H;
    settings.windowMode = OF_WINDOW;
    settings.setGLVersion(3,2);
    ofCreateWindow(settings);
	ofRunApp(new ofApp());
}
