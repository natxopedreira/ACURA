#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // ajustes para la pista
    velocidadPista.setup(HOST, PORT, "/speedTwo");
    
    // gestor de partidas
    partida.setup("/trackOneLap");
    
    // leap–otion
    leap.init();
    
    
    
    
    // gui
    parameters.setName("ajustes pista");
    parameters.add(drawSpeed.set("drawSpeed", true));
    parameters.add(velocidadPista.ajustes);
    parameters.add(velocidadPista.ajustesTween);
    parameters.add(leap.ajustesLeap);
    
    gui.setup(parameters);
    gui.loadFromFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::update(){
    leap.update();
    velocidadPista.update(leap.getDistance());
    partida.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    leap.draw(200,200);
    
    if(drawSpeed) velocidadPista.draw(400, 200);
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}