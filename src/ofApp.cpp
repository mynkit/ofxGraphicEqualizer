#include "ofApp.h"

#define BUFFERSIZE 256; // バッファサイズ(256推奨．大きくすると処理に余裕はでるが遅延が長くなる)
#define SAMPLERATE 44100; // サンプルレート(Hz)

//--------------------------------------------------------------
void ofApp::setup(){
    // audio setup
    bufferSize = BUFFERSIZE;
    sampleRate = SAMPLERATE;
    inputBuffer.resize(bufferSize);
    ofSoundStreamSettings settings;
    settings.setOutListener(this);
    settings.setInListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels=2;
    settings.numInputChannels=1;
    settings.bufferSize = bufferSize;
    sound_stream.setup(settings);

    myEqualizer = new equalizer(sampleRate);
    
    // img
    backgroundImg.load("equalizer_code.png");
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    // バックグラウンド
    ofSetColor(255, 255, 255, 255);
    backgroundImg.draw(0, 0, ofGetWidth(), ofGetHeight());
    // イコライザー
    ofSetColor(180, 180, 200, 200);
    ofDrawRectangle(100,100,360,310);
    // ON/OFFスイッチ
    ofSetColor(50, 50, 50, 200);
    ofDrawCircle(280, 345, 16);
    ofSetColor(210, 210, 210, 200);
    ofDrawCircle(280, 345, 15);
    // イコライザーのつまみ部分
    ofSetColor(80, 80, 80, 150);
    ofDrawRectangle(160,200,10,100);
    ofDrawRectangle(200,200,10,100);
    ofDrawRectangle(240,200,10,100);
    ofDrawRectangle(280,200,10,100);
    ofDrawRectangle(320,200,10,100);
    ofDrawRectangle(360,200,10,100);
    ofDrawRectangle(400,200,10,100);
    ofSetColor(50, 50, 50, 255);
    ofDrawBitmapString("Equalizer", 245, 150);
    ofDrawBitmapString("+12", 120, 215);
    ofDrawBitmapString("+6", 120, 235);
    ofDrawBitmapString(" 0", 120, 255);
    ofDrawBitmapString("-6", 120, 275);
    ofDrawBitmapString("-12", 120, 295);
    //
    ofDrawLine(173, 210, 197, 210);
    ofDrawLine(173, 230, 197, 230);
    ofDrawLine(173, 250, 197, 250);
    ofDrawLine(173, 270, 197, 270);
    ofDrawLine(173, 290, 197, 290);
    //
    ofDrawLine(213, 210, 233, 210);
    ofDrawLine(213, 230, 233, 230);
    ofDrawLine(213, 250, 233, 250);
    ofDrawLine(213, 270, 233, 270);
    ofDrawLine(213, 290, 233, 290);
    //
    ofDrawLine(253, 210, 273, 210);
    ofDrawLine(253, 230, 273, 230);
    ofDrawLine(253, 250, 273, 250);
    ofDrawLine(253, 270, 273, 270);
    ofDrawLine(253, 290, 273, 290);
    //
    ofDrawLine(293, 210, 313, 210);
    ofDrawLine(293, 230, 313, 230);
    ofDrawLine(293, 250, 313, 250);
    ofDrawLine(293, 270, 313, 270);
    ofDrawLine(293, 290, 313, 290);
    //
    ofDrawLine(333, 210, 353, 210);
    ofDrawLine(333, 230, 353, 230);
    ofDrawLine(333, 250, 353, 250);
    ofDrawLine(333, 270, 353, 270);
    ofDrawLine(333, 290, 353, 290);
    //
    ofDrawLine(373, 210, 393, 210);
    ofDrawLine(373, 230, 393, 230);
    ofDrawLine(373, 250, 393, 250);
    ofDrawLine(373, 270, 393, 270);
    ofDrawLine(373, 290, 393, 290);
    if (equalizerOn) {
        // イコライザーがONのときの表示
//        gain100 = 10.;
//        gain200 = 5.;
//        gain400 = 0.;
//        gain800 = -5.;
//        gain1600 = 2.5;
//        gain3200 = 7.5;
//        gain6400 = 12.;
        ofSetColor(200, 10, 10, 200);
        ofDrawRectangle(160,215,9,9);
        ofDrawRectangle(200,227,9,9);
        ofDrawRectangle(240,245,9,9);
        ofDrawRectangle(280,257,9,9);
        ofDrawRectangle(320,227,9,9);
        ofDrawRectangle(360,218,9,9);
        ofDrawRectangle(400,205,9,9);
    }
    
}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer &buffer){
    const int frames = buffer.getNumFrames();
    float curVol = 0.0;
    for(int i = 0; i < frames; i++){
        inputBuffer[i] = buffer[i];
        curVol += inputBuffer[i] * inputBuffer[i];
    }
}

//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer &buffer){
    const int frames = buffer.getNumFrames();
    for(int i = 0; i < frames; i++){
        const int channels = buffer.getNumChannels();
        float currentSample = inputBuffer[i];
        if (equalizerOn) {
            currentSample = myEqualizer->effect(currentSample);
        }
        buffer[i*channels+0] = currentSample;
        buffer[i*channels+1] = currentSample;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
    case 'p':
        if (equalizerOn) {
            equalizerOn = false;
        } else {
            equalizerOn = true;
        }
    }
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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

//--------------------------------------------------------------
void ofApp::exit(){
    ofSoundStreamClose();
}
