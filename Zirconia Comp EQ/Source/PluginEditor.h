/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Components/MiddleKnob.h"
#include "Components/leftKnob.h"
#include "Components/rightKnob.h"

//==============================================================================
/**
*/
class ZirconiaCompEQAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                            public juce::Slider::Listener,
                                            public juce::Button::Listener
{
public:
    ZirconiaCompEQAudioProcessorEditor (ZirconiaCompEQAudioProcessor&);
    ~ZirconiaCompEQAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(juce::Slider * slider) override;
    void buttonClicked(juce::Button * button) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ZirconiaCompEQAudioProcessor& audioProcessor;
    
    juce::Slider pivotKnob;
    juce::Slider EQknob;
    juce::Slider gainKnob;
    juce::ToggleButton bypass;
    
    LeftKnob leftKnob;
    MiddleKnob middleKnob;
    RightKnob rightKnob;
    
    juce::LookAndFeel_V3 lookAndFeel3;
    
    juce::DrawableText pivotLabel;
    juce::Image footswitch;
    juce::Image fullLogo;
    juce::Image eqText;
    juce::Image volumeText;
    juce::Image onText;
    juce::Image offText;
    juce::Image light;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ZirconiaCompEQAudioProcessorEditor)
};
