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
    ofRectangle bounds = outline.getBoundingBox();
    voro::container_poly_2d* con = new voro::container_poly_2d(bounds.x, bounds.x+bounds.getWidth(), bounds.y, bounds.y+bounds.getHeight(), 1, 1, false, false, 16);
    voro::c_loop_all_2d* vl = new voro::c_loop_all_2d(*con);
    voro::voronoicell_2d conCell;

    ofFill();
    ofSetLineWidth(1);
    
    auto len = outline.size();
    
    for (int i=0; i < len; i++) {
        voro::wall_plane_2d * newPlane;

        ofPoint currP(outline[(i)%len]);
        ofPoint nextP(outline[(i+1)%len]);
        double angle = getPositiveDegrees(currP, nextP);
        
        // assume wall will calculate vector back to 0,0
        // so we need to give normal vector [x, y]
        ofPoint normalised(getNormalised(currP,nextP));
        ofVec2f perp = ofVec2f( getNormalised(currP,nextP) ).getPerpendicular().getPerpendicular().getPerpendicular();
        ofPoint normalV(perp);
        ofPoint topLeft(0,0);
        ofPoint offsetV = intersection(topLeft, normalV, currP, nextP);
        double offset = topLeft.distance(offsetV);
        
        if( (angle > 65 && angle < 180) ) {
            newPlane = new voro::wall_plane_2d(perp.x, perp.y, -offset, i);
        } else {
            newPlane = new voro::wall_plane_2d(perp.x, perp.y, offset, i);
        }
        
        con->add_wall(newPlane);
    }

    ofNoFill();

    for(int i=0; i<points.size(); i++) {
        con->put(i, points[i].x, points[i].y, 0);
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
    outline.draw();

    ofPopStyle();
}

//--------------------------------------------------------------
void ofxVoronoi::setBounds(ofRectangle _bounds) {
    outline = ofPolyline::fromRectangle( _bounds );
}

void ofxVoronoi::setBounds(ofPolyline _outline) {
    outline = _outline;
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
    return outline.getBoundingBox();
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

ofPoint ofxVoronoi::intersection(ofPoint p1, ofPoint p2, ofPoint p3, ofPoint p4) {
    
    ofPoint ret((double)-1,(double)-1);
    
    // Store the values for fast access and easy
    // equations-to-code conversion
    double x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
    double y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;
    
    double d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    // If d is zero, there is no intersection
    if (d == 0) return ret;
    
    // Get the x and y
    double pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
    double x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
    double y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;
    
    ret.x = x;
    ret.y = y;

    return ret;
}

ofPoint ofxVoronoi::getNormalised(ofPoint p1, ofPoint p2) {
    double length = getDistance(p1, p2);
    return ofPoint((double)(p2.x - p1.x) / length, (double)(p2.y - p1.y) / length);
}

ofPoint ofxVoronoi::getMidPoint(ofPoint p1, ofPoint p2) {
    return ofPoint((double)(p1.x+p2.x)/2,(double)(p1.y+p2.y)/2);
}

double ofxVoronoi::getDistance(glm::vec3 p1, glm::vec3 p2){
    return glm::distance(p1, p2);
}

double ofxVoronoi::getDistance(ofPoint p1, ofPoint p2){
    return p1.distance(p2);
}

double ofxVoronoi::getRadians(ofPoint p1, ofPoint p2) {
    return atan2(p1.y - p2.y, p1.x - p2.x);
}

double ofxVoronoi::getDegrees(ofPoint p1, ofPoint p2) {
    return getRadians(p1, p2) * 180 / PI;
}
double ofxVoronoi::getPositiveDegrees(ofPoint p1, ofPoint p2) {
    double degrees = fmod(getDegrees(p1, p2), 360);
    while(degrees < 0.0) {
        degrees += 360.0;
    }
    return degrees;
}
