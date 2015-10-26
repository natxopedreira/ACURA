//
//  speedTrack.h
//  playerTest
//
//  Created by Natxo Pedreira gonzalez on 19/9/15.
//
//

#ifndef __playerTest__speedTrack__
#define __playerTest__speedTrack__

#include "ofMain.h"
#include "ofxTween.h"
#include "ofxOsc.h"

class speedTrack {
private:
    
    // vars
    ofParameter<int> velocidadMinima;
    ofParameter<int> velocidadMaxima;
    ofParameter<int> velocidadRaw;
    ofParameter<int> velocidad;
    
    ofParameter<bool> simulacion;
    ofParameter<bool> drawSim;
    
    ofParameter<bool> expo;
    ofParameter<bool> quad;
    ofParameter<bool> cubic;
    ofParameter<bool> sine;
    ofParameter<bool> quart;
    
    string nombre;
    
    // tween
    ofxEasingQuad easeQuad;
    ofxEasingCubic easeCubic;
    ofxEasingSine easeSine;
    ofxEasingQuart easeQuart;
    
    void calcSpeed();
    
    ofPolyline curveQuad, curveCubic, curveSine, curveQuart;
    
    ofxOscSender sender;
    
public:
    
    // gui
    ofParameterGroup ajustes;
    ofParameterGroup ajustesTween;
    
    void setup(string _arduIp, int _arduPort, string _nombre);
    void update(int _speedRaw);
    void draw(int _x, int _y);
    
    int getSpeed();
};

#endif /* defined(__playerTest__speedTrack__) */
