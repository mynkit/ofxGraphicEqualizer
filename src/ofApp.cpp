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
    ofDrawBitmapString("100", 154, 190);
    ofDrawBitmapString("200", 194, 190);
    ofDrawBitmapString("400", 234, 190);
    ofDrawBitmapString("800", 274, 190);
    ofDrawBitmapString("1600", 310, 190);
    ofDrawBitmapString("3200", 350, 190);
    ofDrawBitmapString("6400", 390, 190);
    // gainを見やすくするための補助線
    int x = 173;
    int y = 210;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            ofDrawLine(x + j * 40, y + i * 20, x + 20 + j * 40, y + i * 20);
        }
    }
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
    if ( (button == 0) && (pow(x - 280, 2) + pow(y - 345, 2) <= pow(16, 2)) ) {
        if (equalizerOn) {
            equalizerOn = false;
        } else {
            equalizerOn = true;
        }
    }
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
