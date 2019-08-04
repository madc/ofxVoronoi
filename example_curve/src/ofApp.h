#pragma once

#include "ofMain.h"
#include "ofxVoronoi.h"

class ofApp : public ofBaseApp{

private:

    // For legacy openGL format change OF_USE_LEGACY_VECTOR_MATH to 1 in ofConstants.h
    // and also you could use explicit ofPoint instead of glm:vec3 in ofApp.hpp and ofApp.cpp
    vector<ofDefaultVec3> points;
    ofPolyline curve;
    ofxVoronoi voronoi;

    bool isBorder(ofDefaultVec3 _pt);

public:

    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
};
