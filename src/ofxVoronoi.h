#pragma once

// openFrameworks
#include "ofMain.h"

// Voro++2D
#include "config.h"
#include "common.h"
#include "cell_2d.h"
#include "v_base_2d.h"
#include "rad_option.h"
#include "container_2d.h"
#include "v_compute_2d.h"
#include "c_loops_2d.h"
#include "wall_2d.h"
#include "cell_nc_2d.h"
#include "ctr_boundary_2d.h"

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
    void generate();
    void draw();
    
    bool isBorder(ofPoint _pt);
    
    void setBounds(ofRectangle _bounds);
    void setPoints(vector<ofPoint> _points);
    void addPoint(ofPoint _point);
    void addPoints(vector<ofPoint> _points);
    
    ofRectangle getBounds();
    vector<ofPoint> getPoints();
    vector <ofxVoronoiCell> getCells();
    ofxVoronoiCell& getCell(ofPoint _point);
};