#include "ofMain.h"
#include "ofApp.h"
#include "Constants.h"

int main()
{
    ofGLWindowSettings settings;
    settings.width = APP_W;
    settings.height = APP_H;
    settings.windowMode = OF_FULLSCREEN;
//    settings.setGLVersion(2,1);
    settings.setGLVersion(3,2);
    ofCreateWindow(settings);
    ofAppGLFWWindow win;
    win.setMultiDisplayFullscreen(true);
	ofRunApp(new ofApp());
}
