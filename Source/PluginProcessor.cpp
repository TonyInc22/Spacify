/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SpacifyAudioProcessor::SpacifyAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, NULL, "Params", createParams())
#endif
{
}

SpacifyAudioProcessor::~SpacifyAudioProcessor()
{
}

//==============================================================================
const juce::String SpacifyAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SpacifyAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SpacifyAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SpacifyAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SpacifyAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SpacifyAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SpacifyAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SpacifyAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SpacifyAudioProcessor::getProgramName (int index)
{
    return {};
}

void SpacifyAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SpacifyAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    sampleRate = getSampleRate();
}

void SpacifyAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SpacifyAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

bool SpacifyAudioProcessor::getFarOutButton() 
{
    return apvts.getRawParameterValue("FAROUTBUTTON")->load();
}
bool SpacifyAudioProcessor::getLiftOffButton()
{
    return apvts.getRawParameterValue("LIFTOFFBUTTON")->load();
}
bool SpacifyAudioProcessor::getOtherWorldlyButton()
{
    return apvts.getRawParameterValue("OTHERWORLDLYBUTTON")->load();
}

float SpacifyAudioProcessor::getFarOutMix()
{
    return apvts.getRawParameterValue("FAROUTMIX")->load();
}
float SpacifyAudioProcessor::getLiftOffMix()
{
    return apvts.getRawParameterValue("LIFTOFFMIX")->load();
}
float SpacifyAudioProcessor::getOtherWorldlyMix()
{
    return apvts.getRawParameterValue("OTHERWORLDLYMIX")->load();
}

void SpacifyAudioProcessor::reverb(float* audioL, float* audioR, int hcFreq, float diff, float decay, float hfDamp, float* uTankPrev, float* lTankPrev)
{
    // Stereo to mono
    //==============================================================================
    float audio = 0.5f * (*audioL + *audioR);

    // Preconditioning
    //==============================================================================
    float a = exp(-2 * juce::MathConstants<float>::pi * hcFreq / sampleRate);
    audio = (1 - a) / (1 - a * pow(audio, -1));

    // Decorrelation
    //==============================================================================
    int AP[4] = {-142, -107, -379, -277};
    for (int i = 0; i < 4; i++)
    {
        audio = (diff + pow(audio, AP[i])) / (1 + diff * pow(audio, AP[i]));
    }

    // Tank
    //==============================================================================
    float uTank = audio, lTank = audio;
    *audioL = 0;
    *audioR = 0;

    uTank += *lTankPrev;
    uTank = (-diff + pow(uTank, -(8 / 29761) * sampleRate)) / (1 - diff * pow(uTank, -(8 / 29761) * sampleRate));
    *audioL += pow(uTank, -353) + pow(uTank, -3627);
    *audioR -= pow(uTank, -1990);
    uTank = pow(uTank, -4453);
    uTank = (1 - hfDamp) / (1 - hfDamp * pow(uTank, -1));
    uTank *= decay;
    *audioL -= pow(uTank, -1228);
    *audioR -= pow(uTank, -187);
    uTank = (-diff + pow(uTank, -1800)) / (1 - diff * pow(uTank, -1800));
    *audioL += pow(uTank, -2673);
    *audioR -= pow(uTank, -1066);
    *uTankPrev = pow(uTank, -3720);

    lTank += *uTankPrev;
    lTank = (-diff + pow(lTank, -(8 / 29761) * sampleRate)) / (1 - diff * pow(lTank, -(8 / 29761) * sampleRate));
    *audioL -= pow(lTank, -2111);
    *audioR += pow(lTank, -2974) + pow(lTank, -266);
    lTank = pow(lTank, -4217);
    lTank = (1 - hfDamp) / (1 - hfDamp * pow(lTank, -1));
    lTank *= decay;
    *audioL -= pow(lTank, -335);
    *audioR -= pow(lTank, -1913);
    lTank = (-diff + pow(lTank, -2656)) / (1 - diff * pow(lTank, -2656));
    *audioL -= pow(lTank, -121);
    *audioR += pow(lTank, -1996);
    *lTankPrev = pow(lTank, -3163);

    *audioL *= 0.6;
    *audioR *= 0.6;
}

void SpacifyAudioProcessor::chorus(float* audioL, float* audioR)
{
    *audioL *= 3;
    *audioR *= 3;
}

void SpacifyAudioProcessor::distortion(float* audioL, float* audioR)
{

}

void SpacifyAudioProcessor::flanger(float* audioL, float* audioR)
{

}

void SpacifyAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    float* channelData[2] = { buffer.getWritePointer(0), (totalNumInputChannels < 2) ? buffer.getWritePointer(0) : buffer.getWritePointer(1) };

    float uTankPrev = 0, lTankPrev = 0;

    for (int sample = 0; sample < buffer.getNumSamples(); sample++)
    {
        if (getFarOutButton()) 
        {
            float clean[2] = { *channelData[0], *channelData[1] };
            
            reverb(channelData[0], channelData[1], 300, 0.3f, 0.5f, 0.7f, &uTankPrev, &lTankPrev);
            chorus(channelData[0], channelData[1]);

            float mix = getFarOutMix();
            *channelData[0] = (1 - mix) * clean[0] + mix * *channelData[0];
            *channelData[1] = (1 - mix) * clean[1] + mix * *channelData[1];
        }

        if (getLiftOffButton()) 
        {

        }

        if (getOtherWorldlyButton())
        {
            
        }

        channelData[0]++;
        channelData[1]++;
    }
}

//==============================================================================
bool SpacifyAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SpacifyAudioProcessor::createEditor()
{
    return new SpacifyAudioProcessorEditor(*this);
}

//==============================================================================
void SpacifyAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SpacifyAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SpacifyAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout SpacifyAudioProcessor::createParams() 
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterBool>("FAROUTBUTTON", "Far Out Button", false));
    params.push_back(std::make_unique<juce::AudioParameterBool>("LIFTOFFBUTTON", "Lift Off Button", false));
    params.push_back(std::make_unique<juce::AudioParameterBool>("OTHERWORLDLYBUTTON", "Other Worldly Button", false));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FAROUTMIX", "Far Out Mix", 0.0f,  100.0f, 100.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("LIFTOFFMIX", "Lift Off Mix", 0.0f, 100.0f, 100.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OTHERWORLDLYMIX", "Other Worldly Mix", 0.0f, 100.0f, 100.0f));

    return { params.begin(), params.end()};
}
