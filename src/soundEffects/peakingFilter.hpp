//
//  peakingFilter.hpp
//  ofxGraphicEqualizer
//
//  Created by keita miyano on 2021/01/30.
//

#pragma once

#include <ofMain.h>

class peakingFilter {
    public:
        float omega;
        float alpha;
        // フィルタ計算用のバッファ変数。
        float in1;
        float in2;
        float out1;
        float out2;
        
        float a0;
        float a1;
        float a2;
        float b0;
        float b1;
        float b2;
    
        float gain;
        
        peakingFilter(int sampleRate, int frequency, float Q, float gain);
        ~peakingFilter();
        float effect(float sample);
        void setGain(float gain);
};
