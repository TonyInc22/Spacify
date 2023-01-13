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
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (700, 300);

    farOutMix.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    farOutMix.setRange(0, 100, 1);
    farOutMix.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 75, 25);
    farOutMix.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    farOutMix.setTextValueSuffix("% Mix");
    farOutMix.setValue(100);
    addAndMakeVisible(&farOutMix);

    liftOffMix.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    liftOffMix.setRange(0, 100, 1);
    liftOffMix.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 75, 25);
    liftOffMix.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    liftOffMix.setTextValueSuffix("% Mix");
    liftOffMix.setValue(100);
    addAndMakeVisible(&liftOffMix);

    otherWorldlyMix.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    otherWorldlyMix.setRange(0, 100, 1);
    otherWorldlyMix.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 75, 25);
    otherWorldlyMix.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    otherWorldlyMix.setTextValueSuffix("% Mix");
    otherWorldlyMix.setValue(100);
    addAndMakeVisible(&otherWorldlyMix);
}

SpacifyAudioProcessorEditor::~SpacifyAudioProcessorEditor()
{
}

//==============================================================================
void SpacifyAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::aliceblue);

    //g.setColour (juce::Colours::black);
    //g.setFont (15.0f);
    //g.drawFittedText ("SPACIFY", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
}

void SpacifyAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    farOutMix.setBounds(25, 205, 200, 75);
    liftOffMix.setBounds(250, 205, 200, 75);
    otherWorldlyMix.setBounds(475, 205, 200, 75);
}
