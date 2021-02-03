//
//  equalizer.cpp
//  ofxGraphicEqualizer
//
//  Created by keita miyano on 2021/01/30.
//

#include "soundEffects/equalizer.hpp"

equalizer::equalizer(int sampleRate) {
    float gain100 = 10.;
    float gain200 = 5.;
    float gain400 = 0.;
    float gain800 = -12.;
    float gain1600 = -6;
    float gain3200 = -4;
    float gain6400 = 1;
    myPeakingFilter100 = new peakingFilter(sampleRate, 100, 2.9, gain100);
    myPeakingFilter200 = new peakingFilter(sampleRate, 200, 2.9, gain200);
    myPeakingFilter400 = new peakingFilter(sampleRate, 400, 2.9, gain400);
    myPeakingFilter800 = new peakingFilter(sampleRate, 800, 2.9, gain800);
    myPeakingFilter1600 = new peakingFilter(sampleRate, 1600, 2.9, gain1600);
    myPeakingFilter3200 = new peakingFilter(sampleRate, 3200, 2.9, gain3200);
    myPeakingFilter6400 = new peakingFilter(sampleRate, 6400, 2.9, gain6400);
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
    upperLeftX = x;
    upperLeftY = y;
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
        ofSetColor(200, 10, 10, 200);
        ofDrawRectangle(x + 60, getGainY(myPeakingFilter100->gain) ,9, 9);
        ofDrawRectangle(x + 100, getGainY(myPeakingFilter200->gain), 9, 9);
        ofDrawRectangle(x + 140, getGainY(myPeakingFilter400->gain), 9, 9);
        ofDrawRectangle(x + 180, getGainY(myPeakingFilter800->gain), 9, 9);
        ofDrawRectangle(x + 220, getGainY(myPeakingFilter1600->gain), 9, 9);
        ofDrawRectangle(x + 260, getGainY(myPeakingFilter3200->gain), 9, 9);
        ofDrawRectangle(x + 300, getGainY(myPeakingFilter6400->gain), 9, 9);
    }
}

float equalizer::getGainY(float gain) {
    return upperLeftY + 145 - 40. * gain / 12.;
}

float equalizer::getGain(int gainY) {
    return ((upperLeftY + 145) - gainY) * 12. / 40.;
}

void equalizer::equalizerSwitch(int x, int y, int button) {
    if (button == 0) {
        if (pow(x - onoffX, 2) + pow(y - onoffY, 2) <= pow(onoffRadius, 2)) {
            if (equalizerOn) {
                equalizerOn = false;
            } else {
                equalizerOn = true;
            }
        }
        if (equalizerOn) {
            if (x >= (upperLeftX + 60) && x <= (upperLeftX + 70)) {
                if (y >= (upperLeftY + 185)) {
                    myPeakingFilter100->setGain(-12.);
                }
                else if (y <= (upperLeftY + 105)) {
                    myPeakingFilter100->setGain(12.);
                } else {
                    myPeakingFilter100->setGain(getGain(y));
                }
            }
            if (x >= (upperLeftX + 100) && x <= (upperLeftX + 110)) {
                if (y >= (upperLeftY + 185)) {
                    myPeakingFilter200->setGain(-12.);
                }
                else if (y <= (upperLeftY + 105)) {
                    myPeakingFilter200->setGain(12.);
                } else {
                    myPeakingFilter200->setGain(getGain(y));
                }
            }
            if (x >= (upperLeftX + 140) && x <= (upperLeftX + 150)) {
                if (y >= (upperLeftY + 185)) {
                    myPeakingFilter400->setGain(-12.);
                }
                else if (y <= (upperLeftY + 105)) {
                    myPeakingFilter400->setGain(12.);
                } else {
                    myPeakingFilter400->setGain(getGain(y));
                }
            }
            if (x >= (upperLeftX + 180) && x <= (upperLeftX + 190)) {
                if (y >= (upperLeftY + 185)) {
                    myPeakingFilter800->setGain(-12.);
                }
                else if (y <= (upperLeftY + 105)) {
                    myPeakingFilter800->setGain(12.);
                } else {
                    myPeakingFilter800->setGain(getGain(y));
                }
            }
            if (x >= (upperLeftX + 220) && x <= (upperLeftX + 230)) {
                if (y >= (upperLeftY + 185)) {
                    myPeakingFilter1600->setGain(-12.);
                }
                else if (y <= (upperLeftY + 105)) {
                    myPeakingFilter1600->setGain(12.);
                } else {
                    myPeakingFilter1600->setGain(getGain(y));
                }
            }
            if (x >= (upperLeftX + 260) && x <= (upperLeftX + 270)) {
                if (y >= (upperLeftY + 185)) {
                    myPeakingFilter3200->setGain(-12.);
                }
                else if (y <= (upperLeftY + 105)) {
                    myPeakingFilter3200->setGain(12.);
                } else {
                    myPeakingFilter3200->setGain(getGain(y));
                }
            }
            if (x >= (upperLeftX + 300) && x <= (upperLeftX + 310)) {
                if (y >= (upperLeftY + 185)) {
                    myPeakingFilter6400->setGain(-12.);
                }
                else if (y <= (upperLeftY + 105)) {
                    myPeakingFilter6400->setGain(12.);
                } else {
                    myPeakingFilter6400->setGain(getGain(y));
                }
            }
        }
    }
}
