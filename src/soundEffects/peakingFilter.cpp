//
//  peakingFilter.cpp
//  ofxGraphicEqualizer
//
//  Created by keita miyano on 2021/01/30.
//

#include "soundEffects/peakingFilter.hpp"

peakingFilter::peakingFilter(int sampleRate, int frequency, float bw, float gain) {
    // frequency: 中心周波数(Hz)
    // bw:  ピークの幅
    // gain: 増幅(dB)

    float omega = 2.0f * M_PI * frequency / sampleRate;
    float alpha = sin(omega) * sinh(log(2.0f) / 2.0 * bw * omega / sin(omega));
    float A     = pow(10.0f, (gain / 40.0f) );
    // フィルタ計算用のバッファ変数。
    in1  = 0.0f;
    in2  = 0.0f;
    out1 = 0.0f;
    out2 = 0.0f;
    
    a0 =  1.0f + alpha / A;
    a1 = -2.0f * cos(omega);
    a2 =  1.0f - alpha / A;
    b0 =  1.0f + alpha * A;
    b1 =  -2.0f * cos(omega);
    b2 =  1.0f - alpha * A;
    
}

float peakingFilter::effect(float sample) {
    float nextSample = b0/a0 * sample + b1/a0 * in1  + b2/a0 * in2 - a1/a0 * out1 - a2/a0 * out2;
    in2  = in1;       // 2つ前の入力信号を更新
    in1  = sample;  // 1つ前の入力信号を更新
    out2 = out1;      // 2つ前の出力信号を更新
    out1 = nextSample; // 1つ前の出力信号を更新
    return nextSample;
}
