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

    auto& params = processor.getParameters();

    AudioParameterFloat* mDryWetParameter = (AudioParameterFloat*)params.getUnchecked(0);
    AudioParameterFloat* mFeedbackParameter = (AudioParameterFloat*)params.getUnchecked(1);
    AudioParameterFloat* mDelayTimeParameter = (AudioParameterFloat*)params.getUnchecked(2);

    mDryWetSlider.setBounds(0, 0, 100, 100);
    mDryWetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mDryWetSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mDryWetSlider.setRange(mDryWetParameter->range.start, mDryWetParameter->range.end);
    mDryWetSlider.setValue(*mDryWetParameter);
    addAndMakeVisible(mDryWetSlider);

    mDryWetSlider.onValueChange = [this, mDryWetParameter] { *mDryWetParameter = mDryWetSlider.getValue(); };
    mDryWetSlider.onDragStart = [mDryWetParameter] { mDryWetParameter->beginChangeGesture(); };
    mDryWetSlider.onDragEnd = [mDryWetParameter] { mDryWetParameter->endChangeGesture(); };

    mFeedbackSlider.setBounds(100, 0, 100, 100);
    mFeedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mFeedbackSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mFeedbackSlider.setRange(mFeedbackParameter->range.start, mFeedbackParameter->range.end);
    mFeedbackSlider.setValue(*mFeedbackParameter);
    addAndMakeVisible(mFeedbackSlider);

    mFeedbackSlider.onValueChange = [this, mFeedbackParameter] { *mFeedbackParameter = mDryWetSlider.getValue(); };
    mFeedbackSlider.onDragStart = [mFeedbackParameter] { mFeedbackParameter->beginChangeGesture(); };
    mFeedbackSlider.onDragEnd = [mFeedbackParameter] { mFeedbackParameter->endChangeGesture(); };

    mDelayTimeSlider.setBounds(200, 0, 100, 100);
    mDelayTimeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mDelayTimeSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mDelayTimeSlider.setRange(mDelayTimeParameter->range.start, mDelayTimeParameter->range.end);
    mDelayTimeSlider.setValue(*mDelayTimeParameter);
    addAndMakeVisible(mDelayTimeSlider);

    mDelayTimeSlider.onValueChange = [this, mDelayTimeParameter] { *mDelayTimeParameter = mDryWetSlider.getValue(); };
    mDelayTimeSlider.onDragStart = [mDelayTimeParameter] { mDelayTimeParameter->beginChangeGesture(); };
    mDelayTimeSlider.onDragEnd = [mDelayTimeParameter] { mDelayTimeParameter->endChangeGesture(); };

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
