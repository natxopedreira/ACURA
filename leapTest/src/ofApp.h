#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "leapDistance.h"
#include "speedTrack.h"
#include "game.h"

#define HOST "192.168.0.177"
#define PORT 10000

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		
    
    leapDistance leap;
    speedTrack velocidadPista;
    game partida;
    
    ofxPanel gui;
    
    ofParameterGroup parameters;
    ofParameter<bool> drawSpeed;
};
