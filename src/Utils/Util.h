#pragma once

#include "ofMain.h"
#ifdef TARGET_WIN32
#include <tlhelp32.h>
#include <locale> 
#include <codecvt> 
#include <propsys.h>
#include <propkey.h>
#include <Rpc.h>
#else
#include <uuid/uuid.h>
#endif
#include "Globals.hpp"

static void setLogToFile(string path)
{
	string yyyymmdd = ofGetTimestampString("%Y%m%d%H%M%S%i");

	// keep maximum num of log file
	ofDirectory dir;
	dir.open(path);
	dir.listDir();
	dir.sort();
	if (dir.size() > 100)
	{
		ofFile log;
		log.open(path + "/" + dir.getName(0));
		log.remove();
	}
	dir.close();

	// set new log file;
	string newLog = path + "/" + yyyymmdd + ".log";
	ofLogToFile(newLog);
}

static void alwaysOnTopWindowForWin()
{
#ifdef TARGET_WIN32
	// window always on top
	HWND AppWindow = GetActiveWindow();
	//SetWindowPos(AppWindow, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE + SWP_NOMOVE);
	SetFocus(AppWindow);
	SetForegroundWindow(AppWindow);
	SetActiveWindow(AppWindow);
#endif
}

static void disableEdgeSwipeGesture()
{
#ifdef TARGET_WIN32
	HWND AppWindow = GetActiveWindow();
	IPropertyStore* pPropStore;
	HRESULT hrReturnValue = SHGetPropertyStoreForWindow(AppWindow, IID_PPV_ARGS(&pPropStore));
	if (SUCCEEDED(hrReturnValue))
	{
		PROPVARIANT var;
		var.vt = VT_BOOL;
		var.boolVal = VARIANT_TRUE;
		hrReturnValue = pPropStore->SetValue(PKEY_EdgeGesture_DisableTouchWhenFullscreen, var);
		pPropStore->Release();
	}
#endif
}

static void drawPlane(float _width, float _height)
{
    Global::scrnQuad.setVertex(0, ofVec3f(0,0,0));
    Global::scrnQuad.setVertex(1, ofVec3f(_width,0,0));
    Global::scrnQuad.setVertex(2, ofVec3f(_width,_height,0));
    Global::scrnQuad.setVertex(3, ofVec3f(0,_height,0));
    
    Global::scrnQuad.setTexCoord(0, ofVec2f(0,0));
    Global::scrnQuad.setTexCoord(1, ofVec2f(_width,0));
    Global::scrnQuad.setTexCoord(2, ofVec2f(_width,_height));
    Global::scrnQuad.setTexCoord(3, ofVec2f(0,_height));
    
    Global::scrnQuad.draw();
}

static void saveImage(ofTexture t, string path, float pct = 1.0)
{
    ofFbo fbo;
    fbo.allocate(t.getWidth(), t.getHeight());
    fbo.begin();
    ofClear(0);
    t.draw(0, 0);
    fbo.end();
    ofPixels p;
    fbo.readToPixels(p);
    p.resize(p.getWidth() * pct, p.getHeight() * pct);
    ofSaveImage(p, path);
}