/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MoonbasePluginDemoAudioProcessorEditor::MoonbasePluginDemoAudioProcessorEditor (MoonbasePluginDemoAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    addAndMakeVisible (showActivationUiButton);
    showActivationUiButton.onClick = [&]()
    {
        MOONBASE_SHOW_ACTIVATION_UI;
    };

    setSize (800, 600);
}

MoonbasePluginDemoAudioProcessorEditor::~MoonbasePluginDemoAudioProcessorEditor()
{
}

//==============================================================================
void MoonbasePluginDemoAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MoonbasePluginDemoAudioProcessorEditor::resized()
{
    MOONBASE_RESIZE_ACTIVATION_UI;
    
    Rectangle<int> activationUiButtonArea (250, 30);
    activationUiButtonArea.setCentre (getLocalBounds ().getCentre ());
    showActivationUiButton.setBounds (activationUiButtonArea);
}
