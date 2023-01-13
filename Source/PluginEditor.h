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
class SpacifyAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                     private juce::Slider::Listener
{
public:
    SpacifyAudioProcessorEditor (SpacifyAudioProcessor&);
    ~SpacifyAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void sliderValueChanged (juce::Slider* slider) override;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SpacifyAudioProcessor& audioProcessor;

    juce::Slider farOutMix;
    juce::Slider liftOffMix;
    juce::Slider otherWorldlyMix;
    juce::TextButton farOutButton {"Far Out"};
    juce::TextButton liftOffButton { "Lift Off"};
    juce::TextButton otherWorldyButton { "Other Wordly" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpacifyAudioProcessorEditor)
};
