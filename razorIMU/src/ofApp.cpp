#include "ofApp.h"

float ofApp::yaw;
float ofApp::pitch;
float ofApp::roll;

float ofApp::offYaw;
float ofApp::offPitch;
float ofApp::offRoll;

float ofApp::rYaw;
float ofApp::rPitch;
float ofApp::rRoll;

//--------------------------------------------------------------
void ofApp::setup(){
    try
    {
        razor = new RazorAHRS(serial_port_name, razor_on_data, razor_on_error, RazorAHRS::YAW_PITCH_ROLL);
    }
    catch(runtime_error &e)
    {
        cout << "  " << (string("Could not create tracker: ") + string(e.what())) << endl;
        return 0;
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::razor_on_data(const float data[])
{
    rYaw = data[0];
    rPitch = data[1];
    rRoll = data[2];
    
    yaw = ofWrap(rYaw - offYaw, -180, 180);
    pitch = ofWrap(rPitch - offPitch, -180, 180);
    roll = ofWrap(rRoll - offRoll, -180, 180);
    
    cout << "yaw:: " << rYaw << " - pitch:: " << (int)pitch << endl;
    //cout << "yaw:: " << (int)(yaw) << " - pitch:: " << (int)pitch << endl;
    //csound->SetChannel("yaw", TWO_PI - ofDegToRad(yaw));
    //csound->SetChannel("pitch", ofDegToRad(pitch));
    //csound->SetChannel("roll", ofDegToRad(roll));
}

//--------------------------------------------------------------
void ofApp::razor_on_error(const string &msg)
{
    cout << "  " << "ERROR: " << msg << endl;
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
