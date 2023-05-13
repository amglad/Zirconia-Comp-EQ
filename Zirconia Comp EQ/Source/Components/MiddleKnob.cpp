#include "MiddleKnob.h"

void MiddleKnob::drawRotarySlider (juce::Graphics& g,
                                      int x,
                                      int y,
                                      int width,
                                      int height,
                                      float sliderPos,
                                      const float rotaryStartAngle,
                                      const float rotaryEndAngle,
                                      juce::Slider& slider)
{
    const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    
    juce::Image spriteScaled = sprite.rescaled(120, 120, juce::Graphics::highResamplingQuality);
    juce::AffineTransform rotator;
    g.drawImageTransformed(spriteScaled, rotator.rotated(angle, (float)(spriteScaled.getWidth()/2), (float)(spriteScaled.getHeight()/2)));
    
}
