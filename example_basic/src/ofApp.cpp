#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("ofxVoronoi / example_basic");
    ofBackground(255);
    
    ofRectangle bounds = ofRectangle(10, 10, ofGetWidth()-20, ofGetHeight()-20);
    
    int pointCount = 255;
    int seed = 33;
    
    vector<ofPoint> points = generateRandomPoints(pointCount, seed, bounds);
    
    voronoi.setBounds(bounds);
    voronoi.setPoints(points);
    
    voronoi.generate();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    voronoi.draw();
    
    // Or feel free to draw the voronoi diagram yourself:
    
//    vector <ofxVoronoiCell> cells = voronoi.getCells();
//    ofRectangle bounds = voronoi.getBounds();
//    
//    ofSetLineWidth(0);
//    ofFill();
//    
//    // Draw bounds
//    ofSetColor(220);
//    ofRect(bounds);
//    
//    ofSetColor(180, 0, 0);
//    
//    for(int i=0; i<cells.size(); i++) {
//        // Draw cell borders
//        ofSetColor(120);
//        for(int j=0; j<cells[i].pts.size(); j++) {
//            ofPoint lastPt = cells[i].pts[cells[i].pts.size()-1];
//            if(j > 0) {
//                lastPt = cells[i].pts[j-1];
//            }
//            ofPoint thisPt = cells[i].pts[j];
//            
//            if(!isBorder(lastPt) || !isBorder(thisPt)) {
//                ofLine(lastPt, thisPt);
//            }
//        }
//        
//        // Draw cell points
//        ofSetColor(180, 0, 0);
//        ofFill();
//        ofCircle(cells[i].pt, 2);
//    }
}

//--------------------------------------------------------------
vector <ofPoint> ofApp::generateRandomPoints(int count, int seed, ofRectangle bounds) {
    vector <ofPoint> points;
    ofSeedRandom(seed);
    
    for(int i=0; i<count; i++) {
        ofPoint newPoint = ofPoint(
            ofRandom(bounds.x, bounds.width),
            ofRandom(bounds.y, bounds.height)
        );
        
        points.push_back(newPoint);
    }
    
    return points;
}

//--------------------------------------------------------------
bool ofApp::isBorder(ofPoint _pt){
    ofRectangle bounds = voronoi.getBounds();
    
    return (_pt.x == bounds.x || _pt.x == bounds.x+bounds.width
            || _pt.y == bounds.y || _pt.y == bounds.y+bounds.height);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
