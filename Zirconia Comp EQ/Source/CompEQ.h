/*
  ==============================================================================

    CompEQ.h
    Created: 10 May 2023 2:02:12pm
    Author:  Mitch Glad

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
class EQ
{
public:
    
    void processBlock(juce::AudioBuffer<float> &buffer, float pot, float pivotFreq);
    
    void processInPlace(float *buffer, float pot, float pivotFreq, float gain_Lin, const int numSamples, const int channel);
    
    void prepareToPlay(float sampleRate, float samplesPerBlock);
    
//    void setKnob (float pot);
//    void setPivotFreq (float pivotFreq);
//    void setGain (float gain_Lin);
    
private:
    
    float Fs;
    int bufferSize;
    
    float R3 = 47000.f;
    float R4 = 47000.f;
    float R5 = 15000.f;
    float R6 = 15000.f;
};
