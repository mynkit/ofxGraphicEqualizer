//
//  equalizer.cpp
//  ofxGraphicEqualizer
//
//  Created by keita miyano on 2021/01/30.
//

#include "soundEffects/equalizer.hpp"

equalizer::equalizer(int sampleRate) {
    gain100 = 10.;
    gain200 = 5.;
    gain400 = 0.;
    gain800 = -5.;
    gain1600 = 2.5;
    gain3200 = 7.5;
    gain6400 = 12.;
    myPeakingFilter100 = new peakingFilter(sampleRate, 100, 0.3, gain100);
    myPeakingFilter200 = new peakingFilter(sampleRate, 200, 0.3, gain200);
    myPeakingFilter400 = new peakingFilter(sampleRate, 400, 0.3, gain400);
    myPeakingFilter800 = new peakingFilter(sampleRate, 800, 0.3, gain800);
    myPeakingFilter1600 = new peakingFilter(sampleRate, 1600, 0.3, gain1600);
    myPeakingFilter3200 = new peakingFilter(sampleRate, 3200, 0.3, gain3200);
    myPeakingFilter6400 = new peakingFilter(sampleRate, 6400, 0.3, gain6400);
    equalizerOn = false;
}

float equalizer::effect(float sample) {
    sample = myPeakingFilter100->effect(sample);
    sample = myPeakingFilter200->effect(sample);
    sample = myPeakingFilter400->effect(sample);
    sample = myPeakingFilter800->effect(sample);
    sample = myPeakingFilter1600->effect(sample);
    sample = myPeakingFilter3200->effect(sample);
    sample = myPeakingFilter6400->effect(sample);
    return sample;
}

void equalizer::drawEqualizer(int x, int y) {
    // イコライザー
    ofSetColor(180, 180, 200, 200);
    ofDrawRectangle(x, y, 360, 310);
    // ON/OFFスイッチ
    onoffX = x + 180;
    onoffY = y + 245;
    onoffRadius = 16;
    ofSetColor(50, 50, 50, 200);
    ofDrawCircle(onoffX, onoffY, onoffRadius);
    ofSetColor(210, 210, 210, 200);
    ofDrawCircle(x + 180, y + 245, 15);
    // イコライザーのつまみ部分
    ofSetColor(80, 80, 80, 150);
    for (int i = 0; i < 7; i++) {
        ofDrawRectangle(x + 60 + i * 40, y + 100, 10, 100);
    }
    ofSetColor(50, 50, 50, 255);
    ofDrawBitmapString("Equalizer", x + 145, y + 50);
    ofDrawBitmapString("+12", x + 20, y + 115);
    ofDrawBitmapString("+6", x + 20, y + 135);
    ofDrawBitmapString(" 0", x + 20, y + 155);
    ofDrawBitmapString("-6", x + 20, y + 175);
    ofDrawBitmapString("-12", x + 20, y + 195);
    ofDrawBitmapString("100", x + 54, y + 90);
    ofDrawBitmapString("200", x + 94, y + 90);
    ofDrawBitmapString("400", x + 134, y + 90);
    ofDrawBitmapString("800", x + 174, y + 90);
    ofDrawBitmapString("1600", x + 210, y + 90);
    ofDrawBitmapString("3200", x + 250, y + 90);
    ofDrawBitmapString("6400", x + 290, y + 90);
    // gainを見やすくするための補助線
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            ofDrawLine(x + 73 + j * 40, y + 110 + i * 20, x + 93 + j * 40, y + 110 + i * 20);
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
        ofDrawRectangle(x + 60, y + 115 ,9, 9);
        ofDrawRectangle(x + 100, y + 127, 9, 9);
        ofDrawRectangle(x + 140, y + 145, 9, 9);
        ofDrawRectangle(x + 180, y + 157, 9, 9);
        ofDrawRectangle(x + 220, y + 127, 9, 9);
        ofDrawRectangle(x + 260, y + 118, 9, 9);
        ofDrawRectangle(x + 300, y + 105, 9, 9);
    }
}

void equalizer::equalizerSwitch(int x, int y, int button) {
    if ( (button == 0) && (pow(x - onoffX, 2) + pow(y - onoffY, 2) <= pow(onoffRadius, 2)) ) {
        if (equalizerOn) {
            equalizerOn = false;
        } else {
            equalizerOn = true;
        }
    }
}
