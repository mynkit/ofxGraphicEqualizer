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
    int x_start = 173;
    int y_start = 210;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            ofDrawLine(x_start + j * 40, y_start + i * 20, x_start + 20 + j * 40, y_start + i * 20);
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

void equalizer::equalizerSwitch(int x, int y, int button) {
    if ( (button == 0) && (pow(x - 280, 2) + pow(y - 345, 2) <= pow(16, 2)) ) {
        if (equalizerOn) {
            equalizerOn = false;
        } else {
            equalizerOn = true;
        }
    }
}
