/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SineWave.h"
#include "Delay.h"
#include "ParameterManager.h"

//==============================================================================
/**
 */
class Week_5_pluginAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    Week_5_pluginAudioProcessor();
    ~Week_5_pluginAudioProcessor() override;
    
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
    //juce::AudioProcessorValueTreeState& getValueTreeState();
    ParameterManager* getParameterManager();
    
private:
    
    SineWave mSineWave1;
    SineWave mSineWave1FMOperator;
    
    Delay mDelayLeft;
    Delay mDelayRight;
    
    std::unique_ptr<ParameterManager> mParameterManager;
    
    //std::unique_ptr<juce::AudioProcessorValueTreeState> mParameterState;
    
    std::array<std::atomic<float>*, TotalNumberParameters> mParameterValues;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Week_5_pluginAudioProcessor)
};