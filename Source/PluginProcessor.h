/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class MoonbasePluginDemoAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    MoonbasePluginDemoAudioProcessor();
    ~MoonbasePluginDemoAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:

    //==============================================================================
    /*
        Moonbase API member

        This handy macro will declare and initialise the Moonbase Client API for you, 
        using your Projucer project's ProjectInfo::companyName, 
        ProjectInfo::projectName and ProjectInfo::versionString

        Using this macro expects, that:
        - you've defined the aforementioned ProjectInfo fields in your Projucer project.
        - you've added a 'moonbase_api_config.json' file as Binary Source to your Projucer project.
    */
    //==============================================================================

        MOONBASE_DECLARE_LICENSING_USING_JUCE_PROJECTINFO

    //==============================================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MoonbasePluginDemoAudioProcessor)
};
