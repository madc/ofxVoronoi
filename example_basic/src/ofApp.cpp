#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("ofxVoronoi / example_basic");
    ofBackground(255);
    
    ofRectangle bounds = ofRectangle(10, 10, ofGetWidth()-20, ofGetHeight()-20);
    
    int pointCount = 255;
    int seed = 3;
    
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
