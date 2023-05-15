/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ZirconiaCompEQAudioProcessor::ZirconiaCompEQAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

ZirconiaCompEQAudioProcessor::~ZirconiaCompEQAudioProcessor()
{
}

//==============================================================================
const juce::String ZirconiaCompEQAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ZirconiaCompEQAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ZirconiaCompEQAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ZirconiaCompEQAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ZirconiaCompEQAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ZirconiaCompEQAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ZirconiaCompEQAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ZirconiaCompEQAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ZirconiaCompEQAudioProcessor::getProgramName (int index)
{
    return {};
}

void ZirconiaCompEQAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ZirconiaCompEQAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    eq.prepareToPlay(sampleRate, samplesPerBlock);
    
}

void ZirconiaCompEQAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ZirconiaCompEQAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ZirconiaCompEQAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    if (!bypassOn){
    }
    else{
        int numSamples = buffer.getNumSamples();

        gain_Lin = std::pow(10.0,gain_dB/20.0);
        
        // update components if the knobs change
        if (pot != potStore || pivotFreq != pivotStore)
        {
            eq.updateComponents(pot, pivotFreq);
        }
        
        for (int c = 0; c < totalNumOutputChannels; ++c)
        {
            for (int n = 0; n < numSamples; ++n)
            {
                float x = buffer.getWritePointer(c)[n];
                float y = eq.processSample(x, c);

                buffer.getWritePointer(c)[n] = y * gain_Lin;
            }
        }
        potStore = pot;
        pivotStore = pivotFreq;
    }
}

//==============================================================================
bool ZirconiaCompEQAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ZirconiaCompEQAudioProcessor::createEditor()
{
    return new ZirconiaCompEQAudioProcessorEditor (*this);
}

//==============================================================================
void ZirconiaCompEQAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ZirconiaCompEQAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ZirconiaCompEQAudioProcessor();
}
