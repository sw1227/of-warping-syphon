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
};
