#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGui.h"
#include "ofxTween.h"

#define HOST "192.168.0.177"
#define PORT 10000

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
        void drawSpeedOne(int _x, int _y);
        void drawSpeedTwo(int _x, int _y);
        void drawSpeedTree(int _x, int _y);
        void drawSpeedFour(int _x, int _y);
    
		ofxOscSender sender;
    
    	ofxPanel gui;
        ofxIntSlider speedTrack01;
        ofxIntSlider speedTrack02;
        ofxIntSlider speedTrack03;
        ofxIntSlider speedTrack04;
    
    
        int speedTrackOneTween;
        int speedTrackTwoTween;
        int speedTrackTreeTween;
        int speedTrackFourTween;
    
        ofxEasingBounce easeBounce;
        ofxEasingCubic easeCubic;
        ofxEasingElastic easeElastic;
        ofxEasingLinear easeLinear;
        ofxEasingQuart easeQuart;
        ofxEasingBack easeBack;
        ofxEasingCirc easeCirc;
        ofxEasingExpo easeExpo;
        ofxEasingQuad easeQuad;
        ofxEasingQuint easeQuint;
        ofxEasingSine easeSine;
    
    
    
        void speedTrackOneChanged(int & speedTrack01);
        void speedTrackTwoChanged(int & speedTrack02);
        void speedTrackThreeChanged(int & speedTrack03);
        void speedTrackFourChanged(int & speedTrack04);
};
