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
class SpacifyAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SpacifyAudioProcessorEditor (SpacifyAudioProcessor&);
    ~SpacifyAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SpacifyAudioProcessor& audioProcessor;

    juce::Slider farOutMix;
    juce::Slider liftOffMix;
    juce::Slider otherWorldlyMix;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> farOutMixAttatchment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> liftOffMixAttatchment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> otherWorldlyMixAttatchment;

    juce::TextButton farOutButton {"Far Out"};
    juce::TextButton liftOffButton { "Lift Off"};
    juce::TextButton otherWorldlyButton { "Other Wordly" };

    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> farOutButtonAttatchment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> liftOffButtonAttatchment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> otherWorldlyButtonAttatchment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpacifyAudioProcessorEditor)
};
