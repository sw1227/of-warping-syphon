#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    time = 0.0;
    omega = 0.0;

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

    // Load shader
    shader.load("","warping.frag");
    
    // Setup Serial Communication
    serial.setup("/dev/cu.usbmodem14201",9600);
    
    swFlag = 0;
    distance = 0;
    
    // Valid distance range
    validDistanceStart = 15;
    validDistanceEnd = 200;
    
    frameCount = 60;
    currentFrameCount = frameCount;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (currentFrameCount == frameCount) {
        
        int bytesRequired = 3;
        unsigned char bytes[bytesRequired];
        int bytesRemaining = bytesRequired;
        while ( bytesRemaining > 0 )
        {
            if ( serial.available() > 0 )
            {
                int bytesArrayOffset = bytesRequired - bytesRemaining;
                int result = serial.readBytes( &bytes[bytesArrayOffset],
                                              bytesRemaining );
                
                if ( result == OF_SERIAL_ERROR )
                {
                    ofLog( OF_LOG_ERROR, "unrecoverable error reading from serial" );
                    break;
                }
                else if ( result == OF_SERIAL_NO_DATA )
                {
                    // nothing was read, try again
                }
                else
                {
                    // we read some data!
                    bytesRemaining -= result;
                    swFlag = bytes[0];
                    distance = int(bytes[2] << 8) + bytes[1];
                    if (!(validDistanceStart <= distance && distance <= validDistanceEnd)) {
                        swFlag = 0;
                    }
                    std::cout << int(swFlag) << endl;
                    std::cout << distance << endl;

                    // Update T(Period) based on distance
                    if (static_cast<int>(swFlag) == 1) {
                        float T = static_cast<float>(distance)/ 30.0;
                        omega = 2.0 * PI / T;
                    } else {
                        omega = 0.0;
                    }
                    
                    serial.flush();
                }
            }
        }
        currentFrameCount = 0;
    }
    currentFrameCount++;
    
    float t = ofGetElapsedTimef();
    float dt = 1.0 / 60.0;
    time += dt * (omega + omega * cos(omega * t));
}

//--------------------------------------------------------------
void ofApp::draw(){
    // 1. Draw warped pen_1.jpg to the screen
    shader.begin();
    shader.setUniformTexture("u_image", image1.getTexture(), 0);
    shader.setUniform2f("u_imageSize", image1.getWidth(), image1.getHeight());
    shader.setUniform1f("u_time", time);
    shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    ofDrawRectangle(0,0,ofGetWidth(), ofGetHeight());
    shader.end();
    // Publish GL Screen to Syphon
    screenOutput.publishScreen();

    // 2. Draw warped pen_2.jpg to the framebuffer
    fbo.begin();
    shader.begin();
    shader.setUniformTexture("u_image", image2.getTexture(), 0);
    shader.setUniform2f("u_imageSize", image2.getWidth(), image2.getHeight());
    shader.setUniform1f("u_time", time);
    shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    ofDrawRectangle(0,0,ofGetWidth(), ofGetHeight());
    shader.end();
    fbo.end();
    // Publish framebuffer texture to Syphon
    textureOutput.publishTexture(&fbo.getTexture());
}
