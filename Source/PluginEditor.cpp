/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SpacifyAudioProcessorEditor::SpacifyAudioProcessorEditor (SpacifyAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Size of the GUI
    setSize (700, 300);

    // Properties of the sliders
    //==============================================================================
    farOutMix.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    farOutMix.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 75, 25);
    farOutMix.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    farOutMix.setTextValueSuffix("% Mix");
    addAndMakeVisible(&farOutMix);
    farOutMixAttatchment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "FAROUTMIX", farOutMix);

    liftOffMix.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    liftOffMix.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 75, 25);
    liftOffMix.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    liftOffMix.setTextValueSuffix("% Mix");
    addAndMakeVisible(&liftOffMix);
    liftOffMixAttatchment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "LIFTOFFMIX", liftOffMix);

    otherWorldlyMix.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    otherWorldlyMix.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 75, 25);
    otherWorldlyMix.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    otherWorldlyMix.setTextValueSuffix("% Mix");
    addAndMakeVisible(&otherWorldlyMix);
    otherWorldlyMixAttatchment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "OTHERWORLDLYMIX", otherWorldlyMix);
    //==============================================================================

    // Properties of the buttons
    //==============================================================================
    farOutButton.setButtonText("Far Out");
    farOutButton.setClickingTogglesState(true);
    addAndMakeVisible(&farOutButton);
    farOutButtonAttatchment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.apvts, "FAROUTBUTTON", farOutButton);

    liftOffButton.setButtonText("Lift Off");
    liftOffButton.setClickingTogglesState(true);
    addAndMakeVisible(&liftOffButton);
    liftOffButtonAttatchment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.apvts, "LIFTOFFBUTTON", liftOffButton);

    otherWorldlyButton.setButtonText("Other Worldly");
    otherWorldlyButton.setClickingTogglesState(true);
    addAndMakeVisible(&otherWorldlyButton);
    otherWorldlyButtonAttatchment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.apvts, "OTHERWORLDLYBUTTON", otherWorldlyButton);
    //==============================================================================

}

SpacifyAudioProcessorEditor::~SpacifyAudioProcessorEditor()
{
}

//==============================================================================
void SpacifyAudioProcessorEditor::paint (juce::Graphics& g)
{
    // Background Colour
    g.fillAll (juce::Colours::aliceblue);

    // Main text properties
    g.setColour (juce::Colours::navy);
    g.setFont (15.0f);
    g.drawFittedText ("SPACIFY", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
}

// Positioning of the GUI components
void SpacifyAudioProcessorEditor::resized()
{
    
    // Positions of the sliders
    //==============================================================================
    farOutMix.setBounds(25, 205, 200, 75);

    liftOffMix.setBounds(250, 205, 200, 75);

    otherWorldlyMix.setBounds(475, 205, 200, 75);
    //==============================================================================

    // Positions of the buttons
    //==============================================================================
    farOutButton.setBounds(50, 30, 150, 150);

    liftOffButton.setBounds(275, 30, 150, 150);

    otherWorldlyButton.setBounds(500, 30, 150, 150);
    //==============================================================================
}

