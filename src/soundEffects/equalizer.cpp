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
