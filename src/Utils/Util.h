#pragma once

#include "ofMain.h"
#ifdef TARGET_WIN32
#include <tlhelp32.h>
#include <locale> 
#include <codecvt> 
#include <propsys.h>
#include <propkey.h>
#include <Rpc.h>
#pragma comment(lib, "Rpcrt4.lib")
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
    Globals::scrnQuad.setVertex(0, ofVec3f(0,0,0));
    Globals::scrnQuad.setVertex(1, ofVec3f(_width,0,0));
    Globals::scrnQuad.setVertex(2, ofVec3f(_width,_height,0));
    Globals::scrnQuad.setVertex(3, ofVec3f(0,_height,0));
    
    Globals::scrnQuad.setTexCoord(0, ofVec2f(0,0));
    Globals::scrnQuad.setTexCoord(1, ofVec2f(_width,0));
    Globals::scrnQuad.setTexCoord(2, ofVec2f(_width,_height));
    Globals::scrnQuad.setTexCoord(3, ofVec2f(0,_height));
    
    Globals::scrnQuad.draw();
}

static string genUUID()
{
#ifdef TARGET_WIN32
    string rtn;
    UUID uuid;
    UuidCreate(&uuid);
    char *str;
    UuidToStringA(&uuid, (RPC_CSTR*)&str);
    rtn = string(str);
    RpcStringFreeA((RPC_CSTR*)&str);
    return rtn;
#else
    uuid_t uuid;
    uuid_generate_random(uuid);
    char s[37];
    uuid_unparse(uuid, s);
    string idstr = s;
    return idstr;
#endif
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

static float getNearestPt(const vector<ofPoint> pts, const ofPoint& target, int& ptIdx)
{
    float bestDistance = 0.0;
    for (int i = 0; i < pts.size(); i++)
    {
        float distance = target.distance(pts.at(i));
        if (distance < bestDistance || i == 0)
        {
            bestDistance = distance;
            ptIdx = i;
        }
    }
    return bestDistance;
}

static vector<ofPoint> getCircularPts(float pRadius, ofPoint orig, int devide)
{
    float angle = PI * 2 / devide;
    
    vector<ofPoint> rtn;
    for (int i = 0; i < devide; i++)
    {
        ofPoint p(orig.x + pRadius * cos(angle * i),
                  orig.y + pRadius * sin(angle * i));
        rtn.push_back(p);
    }
    return rtn;
}

static ofPoint getCircularRdmPos(float pRadius, ofPoint orig, bool bUniDist = false)
{
    float angle = ofRandomuf() * PI * 2;
    
    float radius = 0.0;
    if (bUniDist)
    {
        radius = sqrt(ofRandomuf()) * pRadius;
    }
    else
    {
        radius = ofRandomuf() * pRadius;
    }
    
    float x = orig.x + radius * cos(angle);
    float y = orig.y + radius * sin(angle);
    return ofPoint(x, y);
}

static ofPoint getCircularRdmPos3D(float pRadius, ofPoint orig, bool bUniDist = false)
{
    float angle = ofRandomuf() * PI * 2;
    float t = ofRandomuf() * PI * 2;
    
    float radius = 0.0;
    if (bUniDist)
    {
        radius = sqrt(ofRandomuf()) * pRadius;
    }
    else
    {
        radius = ofRandomuf() * pRadius;
    }
    
    float x = orig.x + radius * cos(angle) * sin(t);
    float y = orig.y + radius * sin(angle) * sin(t);
    float z = orig.z + radius * cos(t);
    return ofPoint(x, y, z);
}

static bool isImgFile(string ext)
{
    if (ext == "jpg" || ext == "JPG" ||
        ext == "png" || ext == "PNG")
    {
        return true;
    }
    else
        return false;
}