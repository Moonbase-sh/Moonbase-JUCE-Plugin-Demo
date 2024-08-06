/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
//==============================================================================
CompanyLogo::CompanyLogo ()
{
    logo = Drawable::createFromImageData (BinaryData::MoonbaseLogo_svg, 
                                          BinaryData::MoonbaseLogo_svgSize);

    #if ANIMATE_COMPANY_LOGO
        jitterX.reset (15);
        jitterY.reset (15);
        startTimerHz (30);
    #endif
}

void CompanyLogo::timerCallback () 
{
    // this is just a simple example of how to animate the logo... this particular code makes the logo shiver
    const auto jitterRange = 0.1f;
    jitterX.setTargetValue (jmap (random.nextFloat(), 0.f, 1.f, -jitterRange, jitterRange));
    jitterY.setTargetValue (jmap (random.nextFloat(), 0.f, 1.f, -jitterRange, jitterRange));
    repaint ();
}

void CompanyLogo::paint (Graphics& g)
{
    const auto width = getWidth ();
    const auto height = getHeight ();
    auto area = getLocalBounds().toFloat().reduced (height * 0.1f);
    
    #if ANIMATE_COMPANY_LOGO
        const auto currentJitterX = jitterX.getNextValue ();
        const auto currentJitterY = jitterY.getNextValue ();
        area = area.translated (width * currentJitterX, height * currentJitterY);
    #endif
    
    if (logo != nullptr)
        logo->drawWithin (g, area, RectanglePlacement::centred, 1.0f);
}

//==============================================================================
//==============================================================================
#if USE_WEB_UI
    


        


#endif

//==============================================================================
//==============================================================================
MoonbasePluginDemoAudioProcessorEditor::MoonbasePluginDemoAudioProcessorEditor (MoonbasePluginDemoAudioProcessor& p)
: 
AudioProcessorEditor (&p), 
audioProcessor (p)
#if USE_WEB_UI
, browserOptions (*audioProcessor.moonbaseClient, webBrowser)
, webBrowser (browserOptions)
#endif
{
    #if USE_WEB_UI
        addAndMakeVisible (webBrowser);
        
        // first start your local development server by running 'yarn && yarn dev' in "Source/VueUI"
        // you might have to adjust your port according to your local development server
        webBrowser.goToURL ("http://localhost:5173");

    #else
        addAndMakeVisible (showActivationUiButton);
        showActivationUiButton.onClick = [&]()
        {
            /*
                Moonbase API member activation UI visibility

                Use this macro to show the activation UI on user interaction like the click of a button.
            */
            MOONBASE_SHOW_ACTIVATION_UI;
        };

        /*
            Moonbase Activation UI member initialization

            Use this macro to initialize the Moonbase Activation UI details.
        */
        jassert (activationUI != nullptr);
        if (activationUI != nullptr)
        {
            // There are a max of 2 lines of text on the welcome screen, define them here
            activationUI->setWelcomePageText ("Weightless", "License Management");

            // Set the spinner logo, this is the little icon inside the spinner, when waiting for web responses
            activationUI->setSpinnerLogo (Drawable::createFromImageData (BinaryData::MoonbaseLogo_svg, 
                                                                        BinaryData::MoonbaseLogo_svgSize));

            // Scale the spinner logo as required for your asset if needed. See Submodules/moonbase_JUCEClient/Assets/Source/SVG/OverlayAssets for ideal assets.
            // activationUI->setSpinnerLogoScale (0.5f);
            
            // Set the company logo, this is the logo that is displayed on the welcome screen and the activated info screen
            activationUI->setCompanyLogo (std::make_unique<CompanyLogo> ());

            // Scale the company logo as required for your asset if needed. 
            // activationUI->setCompanyLogoScale ((0.25f));
        
        }
    #endif

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
    #if USE_WEB_UI
        webBrowser.setBounds (getLocalBounds ());
    #else

        /*
            Moonbase Activation UI member resizing

            Use this macro to make sure the activation UI always fits your plugin/app window.
            
        */
        MOONBASE_RESIZE_ACTIVATION_UI;

        Rectangle<int> activationUiButtonArea (250, 30);
        activationUiButtonArea.setCentre (getLocalBounds ().getCentre ());
        showActivationUiButton.setBounds (activationUiButtonArea);
    #endif
}


