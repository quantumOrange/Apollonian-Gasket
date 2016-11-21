#include "ofApp.h"
#include "ComplexCircle.hpp"
//--------------------------------------------------------------
ComplexCircle c();
void ofApp::setup(){
    cout << "Hellow world?" << endl;
    apollonian.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    apollonian.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
   // auto c = ComplexCircle(100,100,100);
    //c.draw();
    apollonian.draw();
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
