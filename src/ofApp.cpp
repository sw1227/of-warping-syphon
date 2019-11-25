#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    image.load("pen_1.jpg");
    // Set name for Syphon
    output.setName("Main");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    shader.load("","test.frag");
    
    shader.begin();
    shader.setUniformTexture("u_image", image.getTexture(), 0);
    shader.setUniform2f("u_imageSize", image.getWidth(), image.getHeight());
    shader.setUniform1f("u_time", ofGetElapsedTimef());
    shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    ofDrawRectangle(0,0,ofGetWidth(), ofGetHeight());
    shader.end();
    
    // Publish to Syphon
    output.publishScreen();
}
