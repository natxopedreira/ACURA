//
//  leapDistance.cpp
//  example
//
//  Created by Natxo Pedreira gonzalez on 21/9/15.
//
//

#include "leapDistance.h"


//--------------------------------------------------------------
void leapDistance::init(){
    leap.open();
    
    distanciaMapped = 0;
    distanciaRaw = 0;
    mano = false;
    manoAbierta = false;
    
    mapRangeInMax = 350;
    mapRangeInMin = 100;
    
    mapRangeOutMax = 255;
    mapRangeOutMin = 0;
    
    ajustesLeap.setName("settings leap");
    ajustesLeap.add(mapRangeInMin.set("mapRangeInMin", 0 , 0, 500));
    ajustesLeap.add(mapRangeInMax.set("mapRangeInMax", 0 , 0, 500));
    
    ajustesLeap.add(mapRangeOutMin.set("mapRangeOutMin", 0 , 0, 255));
    ajustesLeap.add(mapRangeOutMax.set("mapRangeOutMax", 0 , 0, 255));
}

//--------------------------------------------------------------
void leapDistance::update(){
    
    simpleHands = leap.getSimpleHands();
    mano = false;
    manoAbierta = false;
    
    
    if( leap.isFrameNew() && simpleHands.size() ){
        
        //
        mano = true;
        if(leap.getLeapHands()[0].grabStrength()>.5) manoAbierta = true;
        
        // usamos solo la primera mano
        palmaPoint = simpleHands[0].handPos;
        
        // distancia a la leap mapeada
        distanciaMapped = ofMap(palmaPoint.y, mapRangeInMin, mapRangeInMax, mapRangeOutMin, mapRangeOutMax, true);
        distanciaRaw = (int)palmaPoint.y;
    }
    
    if (!mano || !manoAbierta){
        palmaPoint.y -= 10;
        distanciaMapped = ofMap(palmaPoint.y, mapRangeInMin, mapRangeInMax, mapRangeOutMin, mapRangeOutMax, true);
        distanciaRaw = (int)palmaPoint.y;
    }
}

//--------------------------------------------------------------
void leapDistance::draw(int _x, int _y){
    ofPushStyle();
    
    if(mano){
        ofSetColor(0, 200, 100);
    }else{
        ofSetColor(255, 0, 0);
    }
    
    
    ofDrawBitmapString(ofToString(distanciaMapped), ofPoint(_x, _y));
    
    ofPopStyle();
    
    ofPushStyle();
    
    ofNoFill();
    ofRect(_x, _y + 40, 300, 20);
    
    ofFill();
    ofRect(_x, _y + 40, getDistanceNorm() * 300, 20);
    
    ofPopStyle();
}

//--------------------------------------------------------------
bool leapDistance::hayMano(){
    return mano;
}

//--------------------------------------------------------------
float leapDistance::getDistanceNorm(){
    return ofMap(distanciaMapped,  mapRangeOutMin, mapRangeOutMax, 0.0, 1.0);
}

//--------------------------------------------------------------
int leapDistance::getDistance(){
    return distanciaMapped;
}

//--------------------------------------------------------------
int leapDistance::getDistanceRaw(){
    return distanciaRaw;
}


