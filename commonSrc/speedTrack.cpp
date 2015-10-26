//
//  speedTrack.cpp
//  playerTest
//
//  Created by Natxo Pedreira gonzalez on 19/9/15.
//
//

#include "speedTrack.h"


//--------------------------------------------------------------
void speedTrack::setup(string _arduIp, int _arduPort, string _nombre){
    
    nombre = _nombre;
    
    sender.setup(_arduIp, _arduPort);
    
    ajustes.setName("settings velocidad");
    ajustes.add(simulacion.set("simulacion", true));
    ajustes.add(velocidadRaw.set("velocidad raw", 0 , 0, 255));
    ajustes.add(velocidadMinima.set("minima", 0 , 0, 255));
    ajustes.add(velocidadMaxima.set("maxima", 0 , 0, 255));
    ajustes.add(velocidad.set("velocidad", 0 , 0, 255));
    
    
    ajustesTween.setName("tween");
    ajustesTween.add(expo.set("aplicar tween",true));
    ajustesTween.add(quad.set("quad tween",true));
    ajustesTween.add(cubic.set("cubic tween",true));
    ajustesTween.add(sine.set("sine tween",true));
    ajustesTween.add(quart.set("quart tween",true));
    
    
    for (int i = 0; i <= 100; i+=10) {
        curveQuad.addVertex( ofPoint(i,ofxTween::map(i, 0, 100, 0, -100, true, easeQuad, ofxTween::easeOut)));
        curveCubic.addVertex( ofPoint(i,ofxTween::map(i, 0, 100, 0, -100, true, easeCubic, ofxTween::easeOut)));
        curveQuart.addVertex( ofPoint(i,ofxTween::map(i, 0, 100, 0, -100, true, easeQuart, ofxTween::easeOut)));
        curveSine.addVertex( ofPoint(i,ofxTween::map(i, 0, 100, 0, -100, true, easeSine, ofxTween::easeOut)));
    }
    
}

//--------------------------------------------------------------
void speedTrack::update(int _speedRaw){
    
    velocidad.setMax(velocidadMaxima);
    velocidad.setMin(velocidadMinima);
    
    // si queremos o no simular con el gui
    if (!simulacion) {
        velocidadRaw.set(_speedRaw);
    }
    
    // procesamos pa sacar la velocidad
    calcSpeed();
    
    //
    // enviamos la velocidad al ardu
    ofxOscMessage msg;
    msg.setAddress(nombre);
    msg.addIntArg(velocidad);
    sender.sendMessage(msg);
    
}

//--------------------------------------------------------------
void speedTrack::calcSpeed(){

    // si queremos o no una curva en la velocidad
    if (expo) {
        
        if(quad) velocidad.set(ofxTween::map(velocidadRaw, 0, 255, velocidadMinima, velocidadMaxima, true, easeQuad, ofxTween::easeOut));
        if(cubic) velocidad.set(ofxTween::map(velocidadRaw, 0, 255, velocidadMinima, velocidadMaxima, true, easeCubic, ofxTween::easeOut));
        if(sine) velocidad.set(ofxTween::map(velocidadRaw, 0, 255, velocidadMinima, velocidadMaxima, true, easeSine, ofxTween::easeOut));
        if(quart) velocidad.set(ofxTween::map(velocidadRaw, 0, 255, velocidadMinima, velocidadMaxima, true, easeQuart, ofxTween::easeOut));
        
    }else{
        velocidad.set(ofMap(velocidadRaw, 0, 255,velocidadMinima, velocidadMaxima, true));
    }
}

//--------------------------------------------------------------
int speedTrack::getSpeed(){
    return velocidad;
}


//--------------------------------------------------------------
void speedTrack::draw(int _x, int _y){
    

    
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(_x, _y);
    
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("VELOCIDADES PARA EL ARDUINO", ofPoint(200,85));
    
    ofFill();
    ofSetColor(255, 0, 0);
    ofRect(200, 100, velocidadRaw, 20);
    
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("RAW", ofPoint(140,115));
    
    
    ofNoFill();
    ofSetColor(0, 0, 0);
    ofRect(200, 100, 255, 20);
    
    ofFill();
    ofSetColor(0, 205, 210);
    ofRect(200, 130, velocidad, 20);
    
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("TWEEN", ofPoint(140,145));
    
    ofNoFill();
    ofSetColor(0, 0, 0);
    ofRect(200, 130, 255, 20);
    
    ofFill();
    // recuadro medida
    ofDrawBitmapString("CURVA ACELERACION", ofPoint(200,200));
    
    ofRect(200, 215, 100, 100);
    
    ofSetColor(255, 255, 255);
    ofLine(200 + ofMap(velocidad, velocidadMinima, velocidadMaxima, 0, 100), 215,
           200 + ofMap(velocidad, velocidadMinima, velocidadMaxima, 0, 100), 100 + 215);
    
    ofSetColor(0, 255, 234);
    
    
    ofTranslate(200, 100 + 215);
    
    // curva
    if(quad) curveQuad.draw();
    if(cubic) curveCubic.draw();
    if(sine) curveSine.draw();
    if(quart) curveQuart.draw();
    
    ofPopMatrix();
    ofPopStyle();
}