#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // ajustes para la pista
    velocidadPista.setup(HOST, PORT, "/speedOne");
    
    // gui
    parameters.setName("ajustes pista");
    parameters.add(drawSpeed.set("drawSpeed", true));
    parameters.add(velocidadPista.ajustes);
    parameters.add(velocidadPista.ajustesTween);
    
    gui.loadFont("segoeui.ttf", 11, true, true, 96);
    gui.setDefaultHeight(30);
    gui.setDefaultWidth(300);
    
    gui.setup(parameters);
    gui.loadFromFile("settings.xml");

}

//--------------------------------------------------------------
void ofApp::update(){
    // actualiza y envia el dato en raw para conseguir la velocidad
    // mindwave
    // silla
    // leap
    
    velocidadPista.update(mouseX);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if(drawSpeed) velocidadPista.draw(400, 200);
    
    gui.draw();
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
