#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);

    // Load two images
    image1.load("pen_1.jpg");
    image2.load("pen_2.jpg");

    // Setup Syphon
    screenOutput.setName("ScreenOutput");
    textureOutput.setName("TextureOutput");

    // Setup Framebuffer object
    fbo.allocate(512, 512, GL_RGBA);
    fbo.begin();
    ofClear(255, 255, 255, 0);
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    // 1. Draw warped pen_1.jpg to the screen
    shader.load("","test.frag");
    shader.begin();
    shader.setUniformTexture("u_image", image1.getTexture(), 0);
    shader.setUniform2f("u_imageSize", image1.getWidth(), image1.getHeight());
    shader.setUniform1f("u_time", ofGetElapsedTimef());
    shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    ofDrawRectangle(0,0,ofGetWidth(), ofGetHeight());
    shader.end();
    // Publish GL Screen to Syphon
    screenOutput.publishScreen();

    // 2. Draw warped pen_2.jpg to the framebuffer
    fbo.begin();
    shader.load("","test.frag");
    shader.begin();
    shader.setUniformTexture("u_image", image2.getTexture(), 0);
    shader.setUniform2f("u_imageSize", image2.getWidth(), image2.getHeight());
    shader.setUniform1f("u_time", ofGetElapsedTimef());
    shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    ofDrawRectangle(0,0,ofGetWidth(), ofGetHeight());
    shader.end();
    fbo.end();
    // Publish framebuffer texture to Syphon
    textureOutput.publishTexture(&fbo.getTexture());
}
