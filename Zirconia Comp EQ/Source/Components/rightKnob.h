/*
  ==============================================================================

    rightKnob.h
    Created: 10 May 2023 5:43:15pm
    Author:  Mitch Glad

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class RightKnob : public juce::LookAndFeel_V3
{
public:
    juce::Image sprite = juce::ImageCache::getFromMemory(BinaryData::knobRight_png, BinaryData::knobRight_pngSize);

    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider);

};
