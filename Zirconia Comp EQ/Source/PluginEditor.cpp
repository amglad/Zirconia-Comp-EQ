/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ZirconiaCompEQAudioProcessorEditor::ZirconiaCompEQAudioProcessorEditor (ZirconiaCompEQAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 500);
    
    pivotKnob.addListener(this);
    pivotKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    pivotKnob.setBounds(10, 20, 120, 145);
    pivotKnob.setRange(100.0,900.0,1.0);
    pivotKnob.setValue(500.0);
    pivotKnob.setTextValueSuffix(" Hz");
    pivotKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 25);
    pivotKnob.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colour(255, 208, 65));
    pivotKnob.setColour(juce::Slider::ColourIds::textBoxBackgroundColourId, juce::Colour(255, 208, 65));
    pivotKnob.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colour(180, 30, 22));
    pivotKnob.setLookAndFeel(&leftKnob);
    addAndMakeVisible(pivotKnob);
    
    EQknob.addListener(this);
    EQknob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    EQknob.setBounds(140, 20, 120, 120);
    EQknob.setRange(0.0,1.0,0.001);
    EQknob.setValue(0.5);
    EQknob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    EQknob.setLookAndFeel(&middleKnob);
    addAndMakeVisible(EQknob);

    gainKnob.addListener(this);
    gainKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    gainKnob.setBounds(270, 17, 120, 120);
    gainKnob.setRange(-15.0,15.0,0.1);
    gainKnob.setValue(0.0);
    gainKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    gainKnob.setLookAndFeel(&rightKnob);
    addAndMakeVisible(gainKnob);
    
    bypass.addListener(this);
    bypass.setBounds(170,405,60,60);
    bypass.setAlpha(0.f);
    bypass.setToggleState(audioProcessor.bypassOn, juce::dontSendNotification);
    addAndMakeVisible(bypass);

}

ZirconiaCompEQAudioProcessorEditor::~ZirconiaCompEQAudioProcessorEditor()
{
}

//==============================================================================
void ZirconiaCompEQAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colour(255, 208, 65));

    footswitch = juce::ImageCache::getFromMemory(BinaryData::switchLight_png, BinaryData::switchLight_pngSize);
    footswitch.rescaled(90, 150, juce::Graphics::highResamplingQuality);
    int footWidth = footswitch.getWidth();
    int footHeight = footswitch.getHeight();
    g.drawImage (footswitch, 110, 320, 180, 160, 0, 0, footWidth, footHeight, false);
    
    onText = juce::ImageCache::getFromMemory(BinaryData::on_png, BinaryData::on_pngSize);
    onText.rescaled(30, 25, juce::Graphics::highResamplingQuality);
    int onWidth = onText.getWidth();
    int onHeight = onText.getHeight();
    g.drawImage (onText, 115, 410, 30, 25, 0, 0, onWidth, onHeight, false);
    
    offText = juce::ImageCache::getFromMemory(BinaryData::off_png, BinaryData::off_pngSize);
    offText.rescaled(30, 25, juce::Graphics::highResamplingQuality);
    int offWidth = offText.getWidth();
    int offHeight = offText.getHeight();
    g.drawImage (offText, 255, 410, 30, 25, 0, 0, offWidth, offHeight, false);
    
    fullLogo = juce::ImageCache::getFromMemory(BinaryData::fullLogo_png, BinaryData::fullLogo_pngSize);
    fullLogo.rescaled(380, 80, juce::Graphics::highResamplingQuality);
    int logoWidth = fullLogo.getWidth();
    int logoHeight = fullLogo.getHeight();
    g.drawImage (fullLogo, 10, 210, 380, 80, 0, 0, logoWidth, logoHeight, false);
    
    volumeText = juce::ImageCache::getFromMemory(BinaryData::volume_png, BinaryData::volume_pngSize);
    volumeText.rescaled(65, 18, juce::Graphics::highResamplingQuality);
    int volumeWidth = volumeText.getWidth();
    int volumeHeight = volumeText.getHeight();
    g.drawImage (volumeText, 298, 140, 65, 18, 0, 0, volumeWidth, volumeHeight, false);
    
    eqText = juce::ImageCache::getFromMemory(BinaryData::eq_png, BinaryData::eq_pngSize);
    eqText.rescaled(40, 25, juce::Graphics::highResamplingQuality);
    int eqWidth = eqText.getWidth();
    int eqHeight = eqText.getHeight();
    g.drawImage (eqText, 180, 137, 40, 25, 0, 0, eqWidth, eqHeight, false);
    
    if (audioProcessor.bypassOn)
    {
        repaint();
        light = juce::ImageCache::getFromMemory(BinaryData::light_png, BinaryData::light_pngSize);
        light.rescaled(50, 50, juce::Graphics::highResamplingQuality);
        int lightWidth = light.getWidth();
        int lightHeight = light.getHeight();
        g.drawImage (light, 174, 324, 50, 50, 0, 0, lightWidth, lightHeight, false);
    }

}

void ZirconiaCompEQAudioProcessorEditor::resized()
{

}

void ZirconiaCompEQAudioProcessorEditor::sliderValueChanged(juce::Slider * slider)
{
    if (slider == &EQknob)
    {
        audioProcessor.pot = slider->getValue();
    }
    if (slider == &pivotKnob)
    {
        audioProcessor.pivotFreq = slider->getValue();
    }
    if (slider == &gainKnob)
    {
        audioProcessor.gain_dB = slider->getValue();
    }
}

void ZirconiaCompEQAudioProcessorEditor::buttonClicked(juce::Button *button)
{
    if (button == &bypass){
        audioProcessor.bypassOn = !audioProcessor.bypassOn;
    }
}
