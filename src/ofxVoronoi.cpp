#include "ofxVoronoi.h"

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

//--------------------------------------------------------------
void ofxVoronoi::clear() {
    cells.clear();
    points.clear();
}

//--------------------------------------------------------------
void ofxVoronoi::generate(bool ordered) {
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
                ofxVoronoiCell newCell;
                
                // Get the current point of the cell
                double* currentPoint = con->p[vl->ij]+con->ps*vl->q;
                newCell.centroid = ofDefaultVec3(currentPoint[0], currentPoint[1], 0);
                
                // Get the edgepoints of the cell
                do {
                    float x = currentPoint[0] + 0.5 * conCell.pts[2*k];
                    float y = currentPoint[1] + 0.5 * conCell.pts[2*k+1];
                    
                    ofDefaultVec3 pt = ofDefaultVec3(x, y, 0);
                    newCell.points.push_back(pt);
                    
                    k = conCell.ed[2*k];
                } while(k!=0);
                
                cells.push_back(newCell);
            }
        } while(vl->inc());
    }
    
    // free up the memory
    delete con, vl;
    
    if(ordered) {
        std::vector<ofxVoronoiCell> orderedCells;
        for(auto& p : points) {
            // ofLog() << p;
            orderedCells.push_back(getCell(p));
        }
        cells = orderedCells;
    }
}

//--------------------------------------------------------------
void ofxVoronoi::draw() {
    
    ofPushStyle();
    
    ofSetLineWidth(0);
    
    // Draw cells
    ofFill();

    for(int i=0; i<cells.size(); i++) {
        // Draw cell borders
        ofSetColor(220, 220, 220, 180);
        for(int j=0; j<cells[i].points.size(); j++) {
            size_t p = (j+1) % cells[i].points.size();
            ofDrawLine(cells[i].points[p], cells[i].points[j]);
        }
        // Draw cell points
        ofSetColor(180, 0, 0, 180);
        ofDrawCircle(cells[i].centroid, 2);
    }

    // Draw bounds
    ofSetColor(220, 0, 0, 180);
    ofNoFill();
    ofDrawRectangle(bounds);

    ofPopStyle();
}

//--------------------------------------------------------------
void ofxVoronoi::setBounds(ofRectangle _bounds) {
    bounds = _bounds;
}

//--------------------------------------------------------------
void ofxVoronoi::setPoints(std::vector<ofDefaultVec3> _points) {
    clear();
    points = _points;
}

//--------------------------------------------------------------
void ofxVoronoi::addPoint(ofDefaultVec3 _point) {
    points.push_back(_point);
}

//--------------------------------------------------------------
void ofxVoronoi::addPoints(std::vector<ofDefaultVec3> _points) {
    points.insert( points.end(), _points.begin(), _points.end() );
}

//--------------------------------------------------------------
ofRectangle ofxVoronoi::getBounds() {
    return bounds;
}

//--------------------------------------------------------------
std::vector<ofDefaultVec3>& ofxVoronoi::getPoints() {
    return points;
}

//--------------------------------------------------------------
std::vector<ofxVoronoiCell>& ofxVoronoi::getCells() {
    return cells;
}

//--------------------------------------------------------------
void ofxVoronoi::relax(){
    std::vector<ofDefaultVec3> relaxPts;
    for(int i=0; i<cells.size(); i++) {
        ofPolyline line;
        for (auto p:cells[i].points){
            line.addVertex(p.x, p.y);
        }
        line.close();
        ofDefaultVec3 centroid = line.getCentroid2D();
        relaxPts.push_back(centroid);
    }
    clear();
    points = relaxPts;
    generate();
};

//--------------------------------------------------------------
ofxVoronoiCell& ofxVoronoi::getCell(ofDefaultVec3 _point, bool approximate) {
    if(approximate) {
        ofxVoronoiCell& nearestCell = cells[0];
        float nearestDistance = numeric_limits<float>::infinity();
        for(ofxVoronoiCell& cell : cells) {
            float distance = getDistance(_point, cell.centroid);
            if(distance < nearestDistance) {
                nearestDistance = distance;
                nearestCell = cell;
            }
        }
        return nearestCell;
    } else {
        for(ofxVoronoiCell& cell : cells) {
            if(_point == cell.centroid) {
                return cell;
            }
        }
        ofLogError("ofxVoronoi") << "getCell could not find exact match for " << _point;
        return cells[0];
    }
}

float ofxVoronoi::getDistance(ofPoint p1, ofPoint p2){
    return p1.squareDistance(p2);
}
float ofxVoronoi::getDistance(glm::vec3 p1, glm::vec3 p2){
    return glm::distance2(p1, p2);
}

