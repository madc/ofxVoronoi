#pragma once

// Voro++2D
#include "config.hh"
#include "common.hh"
#include "cell_2d.hh"
#include "v_base_2d.hh"
#include "rad_option.hh"
#include "container_2d.hh"
#include "v_compute_2d.hh"
#include "c_loops_2d.hh"
#include "wall_2d.hh"
#include "cell_nc_2d.hh"
#include "ctr_boundary_2d.hh"

// Triangle
//#include "triangle.h"

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