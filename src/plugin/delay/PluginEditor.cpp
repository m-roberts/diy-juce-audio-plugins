/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (300, 100);

    // Get from 'addParameter' in PluginProcessor.cpp
    auto& params = processor.getParameters();

    AudioParameterFloat* dryWetParameter = (AudioParameterFloat*)params.getUnchecked(0);

    mDryWetSlider.setBounds(0, 0, 100, 100);
    mDryWetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mDryWetSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mDryWetSlider.setRange(dryWetParameter->range.start, dryWetParameter->range.end);
    mDryWetSlider.setValue(*dryWetParameter);
    addAndMakeVisible(mDryWetSlider);

    mDryWetSlider.onValueChange = [this, dryWetParameter] { *dryWetParameter = mDryWetSlider.getValue(); };
    mDryWetSlider.onDragStart = [dryWetParameter] { dryWetParameter->beginChangeGesture(); };
    mDryWetSlider.onDragEnd = [dryWetParameter] { dryWetParameter->endChangeGesture(); };


    AudioParameterFloat* feedbackParameter = (AudioParameterFloat*)params.getUnchecked(1);

    mFeedbackSlider.setBounds(100, 0, 100, 100);
    mFeedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mFeedbackSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mFeedbackSlider.setRange(feedbackParameter->range.start, feedbackParameter->range.end);
    mFeedbackSlider.setValue(*feedbackParameter);
    addAndMakeVisible(mFeedbackSlider);

    mFeedbackSlider.onValueChange = [this, feedbackParameter] { *feedbackParameter = mDryWetSlider.getValue(); };
    mFeedbackSlider.onDragStart = [feedbackParameter] { feedbackParameter->beginChangeGesture(); };
    mFeedbackSlider.onDragEnd = [feedbackParameter] { feedbackParameter->endChangeGesture(); };


    // AudioParameterFloat* delayTimeParameter = (AudioParameterFloat*)params.getUnchecked(2);

    // mDelayTimeSlider.setBounds(200, 0, 100, 100);
    // mDelayTimeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    // mDelayTimeSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    // mDelayTimeSlider.setRange(delayTimeParameter->range.start, delayTimeParameter->range.end);
    // mDelayTimeSlider.setValue(*delayTimeParameter);
    // addAndMakeVisible(mDelayTimeSlider);

    // mDelayTimeSlider.onValueChange = [this, delayTimeParameter] { *delayTimeParameter = mDryWetSlider.getValue(); };
    // mDelayTimeSlider.onDragStart = [delayTimeParameter] { delayTimeParameter->beginChangeGesture(); };
    // mDelayTimeSlider.onDragEnd = [delayTimeParameter] { delayTimeParameter->endChangeGesture(); };

}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void NewProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
