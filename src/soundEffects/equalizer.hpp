//
//  equalizer.hpp
//  ofxGraphicEqualizer
//
//  Created by keita miyano on 2021/01/30.
//

#pragma once

#include "soundEffects/peakingFilter.hpp"

class equalizer {
    public:
        bool equalizerOn;
        float gain100;
        float gain200;
        float gain400;
        float gain800;
        float gain1600;
        float gain3200;
        float gain6400;
        peakingFilter* myPeakingFilter100;
        peakingFilter* myPeakingFilter200;
        peakingFilter* myPeakingFilter400;
        peakingFilter* myPeakingFilter800;
        peakingFilter* myPeakingFilter1600;
        peakingFilter* myPeakingFilter3200;
        peakingFilter* myPeakingFilter6400;
        equalizer(int sampleRate);
        ~equalizer();
        float effect(float sample);
        void drawEqualizer(int x, int y);
        void equalizerSwitch(int x, int y, int button);
};
