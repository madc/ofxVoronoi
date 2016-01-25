#pragma once

// openFrameworks
#include "ofMain.h"

class ofxVoronoiCell {
  public:
    vector<ofPoint> pts;
    ofPoint pt;
};

class ofxVoronoi {
private:
    ofRectangle bounds;
    vector<ofPoint> points;
    vector<ofxVoronoiCell> cells;
    
public:
    ofxVoronoi();
    ~ofxVoronoi();
    
    void clear();
    void generate(bool ordered=true);
    void draw();
    
    bool isBorder(ofPoint _pt);
    
    void setBounds(ofRectangle _bounds);
    void setPoints(vector<ofPoint> _points);
    void addPoint(ofPoint _point);
    void addPoints(vector<ofPoint> _points);
    
    ofRectangle getBounds();
    vector<ofPoint>& getPoints();
    vector <ofxVoronoiCell>& getCells();
    ofxVoronoiCell& getCell(ofPoint _point, bool approximate=false);
    
    //borg
    void relax();
};