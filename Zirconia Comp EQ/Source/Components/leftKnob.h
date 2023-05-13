/*
  ==============================================================================

    leftKnob.h
    Created: 10 May 2023 5:43:11pm
    Author:  Mitch Glad

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class LeftKnob : public juce::LookAndFeel_V3
{
public:
    juce::Image sprite = juce::ImageCache::getFromMemory(BinaryData::knobLeft_png, BinaryData::knobLeft_pngSize);

    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider);

};
