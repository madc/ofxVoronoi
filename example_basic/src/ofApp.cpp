#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("ofxVoronoi / example_basic");
    ofBackground(255);
    
    ofRectangle bounds = ofRectangle(10, 10, ofGetWidth()-20, ofGetHeight()-20);
    
    // Random points
    int pointCount = 255;
    int seed = 33;
    ofSeedRandom(seed);
    for(int i=0; i<pointCount; i++) {
        ofDefaultVec3 newPoint = ofDefaultVec3( ofRandom(bounds.x, bounds.width), ofRandom(bounds.y, bounds.height), 0 );
        points.push_back(newPoint);
    }
    
    // Voronoi setup
    voronoi.setBounds(bounds);
    voronoi.setPoints(points);
    voronoi.generate();
    
    points.clear();
    for(auto cell : voronoi.getCells()) {
        points.push_back(cell.centroid);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    // voronoi.draw();
    
    // Or feel free to draw the voronoi diagram yourself:
    
    ofRectangle bounds = voronoi.getBounds();
    ofSetLineWidth(0);
    ofNoFill();
    ofSetColor(220);
    ofDrawRectangle(bounds);
    
    vector<ofxVoronoiCell> cells = voronoi.getCells();
    for(int i=0; i<cells.size(); i++) {
        ofSetColor(0);
        ofNoFill();
        ofMesh mesh;
        mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
        mesh.addVertices(cells[i].points);
        mesh.draw();
        
        mesh.clear();
        for(int j = 0; j < cells[i].points.size(); j++) {
            mesh.addVertex(cells[i].centroid);
            mesh.addVertex(cells[i].points[j]);
        }
        ofSetColor(120);
        mesh.draw();
        
        // Draw cell points
        ofSetColor(ofColor::fromHsb(255. * i / cells.size(), 255., 255.));
        ofFill();
        ofDrawCircle(cells[i].centroid, 2);
    }
}


//--------------------------------------------------------------
bool ofApp::isBorder(ofDefaultVec3 _pt){
    ofRectangle bounds = voronoi.getBounds();
    
    return (_pt.x == bounds.x || _pt.x == bounds.x+bounds.width
            || _pt.y == bounds.y || _pt.y == bounds.y+bounds.height);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    int n = 0;
    switch(key) {
        case '1': n = 1; break;
        case '2': n = 10; break;
        case '3': n = 100; break;
        case '4': n = 1000; break;
    }
    for(int i = 0; i < n; i++) {
        voronoi.relax();
    }
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
