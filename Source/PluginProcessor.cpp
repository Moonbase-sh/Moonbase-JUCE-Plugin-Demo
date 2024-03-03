/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MoonbasePluginDemoAudioProcessor::MoonbasePluginDemoAudioProcessor()
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

MoonbasePluginDemoAudioProcessor::~MoonbasePluginDemoAudioProcessor()
{
}

//==============================================================================
/*
    Moonbase API implementation starts here
*/
void MoonbasePluginDemoAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    /*
        Moonbase API member audio initialization

        Use this macro to initialize the Moonbase API member for audio processing.
    */
    MOONBASE_PREPARE_TO_PLAY (sampleRate, samplesPerBlock);
}

void MoonbasePluginDemoAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    
    // -- > Your audio processing goes here < -- //

    /*
        Moonbase API member audio processing

        Use this macro to process audio with the Moonbase API member. 
        It's important, that this is the last call in the processBlock method.
        Having this post-process will ensure, that the audio cuts out periodically, 
        if the plugin is not authorized. 
    */
    MOONBASE_PROCESS (buffer);
}

/*
    Moonbase API implementation ends here
*/

//==============================================================================
const juce::String MoonbasePluginDemoAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MoonbasePluginDemoAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MoonbasePluginDemoAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MoonbasePluginDemoAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MoonbasePluginDemoAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MoonbasePluginDemoAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MoonbasePluginDemoAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MoonbasePluginDemoAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MoonbasePluginDemoAudioProcessor::getProgramName (int index)
{
    return {};
}

void MoonbasePluginDemoAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}



void MoonbasePluginDemoAudioProcessor::releaseResources()
{

}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MoonbasePluginDemoAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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



//==============================================================================
bool MoonbasePluginDemoAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MoonbasePluginDemoAudioProcessor::createEditor()
{
    return new MoonbasePluginDemoAudioProcessorEditor (*this);
}

//==============================================================================
void MoonbasePluginDemoAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MoonbasePluginDemoAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MoonbasePluginDemoAudioProcessor();
}
