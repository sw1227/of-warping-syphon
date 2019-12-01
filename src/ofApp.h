#pragma once

#include "ofMain.h"
#include "ofxSyphon.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    ofxSyphonServer screenOutput;
    ofxSyphonServer textureOutput;
    
    ofShader shader;
    ofImage image1;
    ofImage image2;
    ofFbo fbo;

    // Distorted time
    float time;
    
    // For serial communication
    ofSerial serial;
    
    unsigned char swFlag; //0:OFF, 1:ON
    int distance; //distance from ultrasonic sensor (cm)
    int validDistanceStart;
    int validDistanceEnd;
    
    int frameCount;
    int currentFrameCount;
};
