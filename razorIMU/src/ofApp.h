#pragma once

#include "ofMain.h"
#include "RazorAHRS.h"

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
    
    
    
    // Razor head-tracker
    const string                    serial_port_name = "/dev/tty.RNBT-388D-RNI-SPP";
    RazorAHRS                       *razor;
    static void                     razor_on_data(const float data[]);
    static void                     razor_on_error(const string &msg);
    static float                    yaw, pitch, roll, offYaw, offPitch, offRoll, rYaw, rPitch, rRoll;
		
};
