#include "ofxVoronoi.h"

//--------------------------------------------------------------
ofxVoronoi::ofxVoronoi() {}

//--------------------------------------------------------------
ofxVoronoi::~ofxVoronoi() {}

//--------------------------------------------------------------
void ofxVoronoi::clear() {
    cells.clear();
    points.clear();
}

//--------------------------------------------------------------
void ofxVoronoi::generate() {
    voro::container_2d* con = new voro::container_2d(bounds.x, bounds.x+bounds.getWidth(), bounds.y, bounds.y+bounds.getHeight(), 10, 10, false, false, 16);
    voro::c_loop_all_2d* vl = new voro::c_loop_all_2d(*con);
    voro::voronoicell_2d conCell;
        
    for(int i=0; i<points.size(); i++) {
        con->put(i, points[i].x, points[i].y);
    }
    
    if(vl->start()) {
        do {
            con->compute_cell(conCell, *vl);
            int k = 0;
            
            if(conCell.p) {
                ofxVoronoiCell newCell = ofxVoronoiCell();
                
                // Get the current point of the cell
                double* currentPoint = con->p[vl->ij]+con->ps*vl->q;
                newCell.pt = ofPoint(currentPoint[0], currentPoint[1]);
                
                // Get the edgepoints of the cell
                do {
                    float x = currentPoint[0] + 0.5 * conCell.pts[2*k];
                    float y = currentPoint[1] + 0.5 * conCell.pts[2*k+1];
                    newCell.pts.push_back(ofPoint(x, y));
                    
                    k = conCell.ed[2*k];
                } while(k!=0);
                
                cells.push_back(newCell);
            }
        } while(vl->inc());
    }
    
    // free up the memory
    delete con, vl;
}

//--------------------------------------------------------------
void ofxVoronoi::draw() {
    ofSetLineWidth(0);
    ofFill();
    
    // Draw bounds
    ofSetColor(220);
    ofRect(bounds);
    
    ofSetColor(180, 0, 0);

    for(std::vector<ofxVoronoiCell>::iterator it=cells.begin(); it!=cells.end(); ++it) {
        // Draw cell borders
        ofPath path;
        
        path.setStrokeColor(ofColor(180));
        path.setStrokeWidth(1);
        path.setFilled(false);
        
        for(int j=0; j<it->pts.size(); j++) {
            path.lineTo(it->pts[j]);
        }
        
        path.close();
        path.draw();
        
        // Draw cell points
        ofCircle(it->pt, 2);
    }
}

//--------------------------------------------------------------
void ofxVoronoi::setBounds(ofRectangle _bounds) {
    bounds = _bounds;
}

//--------------------------------------------------------------
void ofxVoronoi::setPoints(vector<ofPoint> _points) {
    clear();
    
    points = _points;
}

//--------------------------------------------------------------
void ofxVoronoi::addPoint(ofPoint _point) {
    points.push_back(_point);
}

//--------------------------------------------------------------
void ofxVoronoi::addPoints(vector<ofPoint> _points) {
    for(std::vector<ofPoint>::iterator it=_points.begin(); it!=_points.end(); ++it) {
        addPoint(*it);
    }
}

//--------------------------------------------------------------
ofRectangle ofxVoronoi::getBounds() {
    return bounds;
}

//--------------------------------------------------------------
vector<ofPoint> ofxVoronoi::getPoints() {
    return points;
}

//--------------------------------------------------------------
vector <ofxVoronoiCell> ofxVoronoi::getCells() {
    return cells;
}

//--------------------------------------------------------------
ofxVoronoiCell& ofxVoronoi::getCell(ofPoint _point) {
    for(std::vector<ofxVoronoiCell>::iterator it=cells.begin(); it!=cells.end(); ++it) {
        if(_point == it->pt) {
            return *it;
        }
    }
}
