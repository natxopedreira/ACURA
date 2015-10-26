#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255, 255, 255);
    
    sender.setup(HOST, PORT);
    
    gui.setup(); // most of the time you don't need a name
    gui.add(speedTrack01.setup( "speedTrack01", 0, 0, 255 ));
    gui.add(speedTrack02.setup( "speedTrack02", 0, 0, 255 ));
    gui.add(speedTrack03.setup( "speedTrack03", 0, 0, 255 ));
    gui.add(speedTrack04.setup( "speedTrack04", 0, 0, 255 ));
    
    speedTrack01.addListener(this, &ofApp::speedTrackOneChanged);
    
    
    speedTrackOneTween = speedTrack01;
    speedTrackTwoTween = speedTrack02;
    speedTrackTreeTween = speedTrack03;
    speedTrackFourTween = speedTrack04;
    
}

//--------------------------------------------------------------
void ofApp::update(){

    // tween
    speedTrackOneTween = ofxTween::map(speedTrack01, 0, 255, 0, 255, true, easeQuad, ofxTween::easeOut);
    speedTrackTwoTween = ofxTween::map(speedTrack02, 0, 255, 0, 255, true, easeQuad, ofxTween::easeOut);
    speedTrackTreeTween = ofxTween::map(speedTrack03, 0, 255, 0, 255, true, easeQuad, ofxTween::easeOut);
    speedTrackFourTween = ofxTween::map(speedTrack04, 0, 255, 0, 255, true, easeQuad, ofxTween::easeOut);
    
    
    // enviamos la info
    // de las velocidades pa la pista
    ofxOscMessage mOne;
    mOne.setAddress("/speedOne");
    mOne.addIntArg(speedTrack01);
    sender.sendMessage(mOne);
    
    ofxOscMessage mTwo;
    mTwo.setAddress("/speedTwo");
    mTwo.addIntArg(speedTrack02);
    sender.sendMessage(mTwo);
    
    ofxOscMessage mTree;
    mTree.setAddress("/speedTree");
    mTree.addIntArg(speedTrack03);
    sender.sendMessage(mTree);
    
    ofxOscMessage mFour;
    mFour.setAddress("/speedFour");
    mFour.addIntArg(speedTrack04);
    sender.sendMessage(mFour);
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    gui.draw();
    
    // draw speed bar
    // speed track one
    drawSpeedOne(0, 0);
    drawSpeedTwo(0, 120);
    drawSpeedTree(0, 240);
    drawSpeedFour(0, 360);
}

//--------------------------------------------------------------
void ofApp::drawSpeedOne(int _x, int _y){
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(_x, _y);
    
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("SPEED ONE", ofPoint(200,85));
    
    ofFill();
    ofSetColor(255, 0, 0);
    ofRect(200, 100, speedTrack01, 20);
    
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("NORMAL", ofPoint(140,115));
    
    
    ofNoFill();
    ofSetColor(0, 0, 0);
    ofRect(200, 100, 255, 20);
    
    ofFill();
    ofSetColor(0, 205, 210);
    ofRect(200, 130, speedTrackOneTween, 20);
    
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("TWEEN", ofPoint(140,145));
    
    ofNoFill();
    ofSetColor(0, 0, 0);
    ofRect(200, 130, 255, 20);
    
    ofPopMatrix();
    ofPopStyle();
}
//--------------------------------------------------------------
void ofApp::drawSpeedTwo(int _x, int _y){
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(_x, _y);
    
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("SPEED TWO", ofPoint(200,85));
    
    ofFill();
    ofSetColor(255, 0, 0);
    ofRect(200, 100, speedTrack02, 20);
    
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("NORMAL", ofPoint(140,115));
    
    
    ofNoFill();
    ofSetColor(0, 0, 0);
    ofRect(200, 100, 255, 20);
    
    ofFill();
    ofSetColor(0, 205, 210);
    ofRect(200, 130, speedTrackTwoTween, 20);
    
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("TWEEN", ofPoint(140,145));
    
    ofNoFill();
    ofSetColor(0, 0, 0);
    ofRect(200, 130, 255, 20);
    
    ofPopMatrix();
    ofPopStyle();
}
//--------------------------------------------------------------
void ofApp::drawSpeedTree(int _x, int _y){
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(_x, _y);
    
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("SPEED TREE", ofPoint(200,85));
    
    ofFill();
    ofSetColor(255, 0, 0);
    ofRect(200, 100, speedTrack03, 20);
    
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("NORMAL", ofPoint(140,115));
    
    
    ofNoFill();
    ofSetColor(0, 0, 0);
    ofRect(200, 100, 255, 20);
    
    ofFill();
    ofSetColor(0, 205, 210);
    ofRect(200, 130, speedTrackTreeTween, 20);
    
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("TWEEN", ofPoint(140,145));
    
    ofNoFill();
    ofSetColor(0, 0, 0);
    ofRect(200, 130, 255, 20);
    
    ofPopMatrix();
    ofPopStyle();
}
//--------------------------------------------------------------
void ofApp::drawSpeedFour(int _x, int _y){
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(_x, _y);
    
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("SPEED FOUR", ofPoint(200,85));
    
    ofFill();
    ofSetColor(255, 0, 0);
    ofRect(200, 100, speedTrack04, 20);
    
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("NORMAL", ofPoint(140,115));
    
    
    ofNoFill();
    ofSetColor(0, 0, 0);
    ofRect(200, 100, 255, 20);
    
    ofFill();
    ofSetColor(0, 205, 210);
    ofRect(200, 130, speedTrackFourTween, 20);
    
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("TWEEN", ofPoint(140,145));
    
    ofNoFill();
    ofSetColor(0, 0, 0);
    ofRect(200, 130, 255, 20);
    
    ofPopMatrix();
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::speedTrackOneChanged(int & speedTrack01){
    ofxOscMessage m;
    m.setAddress("/speedOne");
    m.addIntArg(speedTrack01);
    sender.sendMessage(m);
}

//--------------------------------------------------------------
void ofApp::speedTrackTwoChanged(int & speedTrack02){
    ofxOscMessage m;
    m.setAddress("/speedTwo");
    m.addIntArg(speedTrack02);
    sender.sendMessage(m);
}

//--------------------------------------------------------------
void ofApp::speedTrackThreeChanged(int & speedTrack03){
    ofxOscMessage m;
    m.setAddress("/speedTree");
    m.addIntArg(speedTrack03);
    sender.sendMessage(m);
}

//--------------------------------------------------------------
void ofApp::speedTrackFourChanged(int & speedTrack04){
    ofxOscMessage m;
    m.setAddress("/speedFour");
    m.addIntArg(speedTrack04);
    sender.sendMessage(m);
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
