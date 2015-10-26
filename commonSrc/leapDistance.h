//
//  leapDistance.h
//  example
//
//  Created by Natxo Pedreira gonzalez on 21/9/15.
//
//

#ifndef __example__leapDistance__
#define __example__leapDistance__

#include "ofMain.h"
#include "ofxLeapMotion2.h"


class leapDistance {
    ofxLeapMotion leap;
    vector <ofxLeapMotionSimpleHand> simpleHands;
    ofPoint palmaPoint;
    
    ofParameter<int> distanciaRaw;
    ofParameter<int> distanciaMapped;
    
    ofParameter<int> mapRangeInMax;
    ofParameter<int> mapRangeInMin;

    ofParameter<int> mapRangeOutMax;
    ofParameter<int> mapRangeOutMin;
    
    bool mano;
    bool manoAbierta;
    
public:
    void init();
    void update();
    void draw(int _x, int _y);
    
    int getDistance();
    int getDistanceRaw();
    
    float getDistanceNorm();
    
    bool hayMano();
    
    ofParameterGroup ajustesLeap;
};

#endif /* defined(__example__leapDistance__) */
