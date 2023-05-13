#ifndef MIDDLEKNOB_H_INCLUDED
#define MIDDLEKNOB_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class MiddleKnob : public juce::LookAndFeel_V3
{
public:
    juce::Image sprite = juce::ImageCache::getFromMemory(BinaryData::compKnob_png, BinaryData::compKnob_pngSize);

    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider);

};

#endif /* MIDDLEKNOB_H_INCLUDED */
