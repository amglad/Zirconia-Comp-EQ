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
    
    void processInPlace(float *buffer, float gain_Lin, const int numSamples, const int channel);
    
    float processSample(float x, int c);
    
    void updateComponents(double pot, double pivotFreq);
    
    void prepareToPlay(double sampleRate, int samplesPerBlock);
    
//    void setKnob (float pot);
//    void setPivotFreq (float pivotFreq);
//    void setGain (float gain_Lin);
    
private:
    
    double Fs;
    double Ts;
    int bufferSize;
    
    double R3 = 47000.0;
    double R4 = 47000.0;
    double R5 = 15000.0;
    double R6 = 15000.0;
    
    double b0;
    double b1;
    double b2;
    
    double R1;
    double R2;
    
    double Gw;
    double Gx;
    double Gy;
    double Gz;
    
    double x1[2];
    double x2[2];
    
    

};
