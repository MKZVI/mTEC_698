/*
  ==============================================================================

    SineWave.cpp
    Created: 27 Feb 2022 2:08:21pm
    Author:  Micah Keren-Zvi

  ==============================================================================
*/

#include <stdio.h>
#include "SineWave.h"

SineWave::SineWave() {
    
}

SineWave::~SineWave() {
    
}

void SineWave::initialize(float inFrequencyHz, float inSampleRate) {
    
    // Set our desired frequency in HZ
    mFreqHz = inFrequencyHz;
    
    // Set our samplerate for math calculations
    mSampleRate = inSampleRate;
    
    mSmoothedGain.reset(inSampleRate, 0.01);
}

float SineWave::getNextSample() {
    
    // calculate our sine function output -- using a sin call scaled to repete between 0 - 1 on the input
    float output = std::sin(juce::MathConstants<float>::twoPi * mPhase);
    
    // move our phase forward in the sign table by a single step determined by our desired samplerate & playback hz
    mPhase += mFreqHz / mSampleRate;
    
    // if we go passed 1 -- lets loop back around the sine wave
    if (mPhase > 1.f) {
        mPhase -= 1.f;
    }
    
    // return the output to the caller
    return output * mSmoothedGain.getNextValue();
}

float SineWave::getNextSampleWithFM(float inFMOperator)
{
    float output = std::sin(juce::MathConstants<float>::twoPi * (mPhase + inFMOperator));
    
    // move our phase forward in the sign table by a single step determined by our desired samplerate & playback hz
    mPhase += mFreqHz / mSampleRate;
    
    // if we go passed 1 -- lets loop back around the sine wave
    if (mPhase > 1.f) {
        mPhase -= 1.f;
    }
    
    // return the output to the caller
    return output * mSmoothedGain.getNextValue();
}

/* */
void SineWave::setGain(float inGain)
{
    mSmoothedGain.setTargetValue(inGain);
}

float SineWave::getGain()
{
    return mSmoothedGain.getTargetValue();
}

float SineWave::setFreq(float newFreq)
{
    mFreqHz = newFreq;
    
    return newFreq;
}
