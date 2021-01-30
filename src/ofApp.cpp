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
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

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
        if (peakingFilterOn) {
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
        if (peakingFilterOn) {
            peakingFilterOn = false;
        } else {
            peakingFilterOn = true;
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
