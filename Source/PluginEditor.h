/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MoonbasePluginDemoAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    MoonbasePluginDemoAudioProcessorEditor (MoonbasePluginDemoAudioProcessor&);
    ~MoonbasePluginDemoAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MoonbasePluginDemoAudioProcessor& audioProcessor;
    
    //==============================================================================
    /*
        Moonbase Activation UI member

        This handy macro will declare and initialise the Moonbase Activation UI for you. 
        For this to work you have to declare a Moonbase API member in your AudioProcessor class, 
        called 'moonbaseClient'. 

        Once added, you'll only have to add the MOONBASE_RESIZE_ACTIVATION_UI to your AudioProcessorEditor::resized () method
        and you can call MOONBASE_SHOW_ACTIVATION_UI whenever you want to show the activation UI (e.g. when clicking a button)

        Activation UI visibility in relation to activation state is managed automatically - you can only SHOW the UI, 
        using this macro, never hide it, that's all managed internally.
    */
    //==============================================================================
        
        MOONBASE_DECLARE_AND_INIT_ACTIVATION_UI (audioProcessor);
    
    //==============================================================================

    TextButton showActivationUiButton { "Show Activation UI" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MoonbasePluginDemoAudioProcessorEditor)
};
