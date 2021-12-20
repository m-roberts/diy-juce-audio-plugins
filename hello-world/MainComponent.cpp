#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (1200, 800);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::purple);

    juce::Font mainComponentFont("Times New Roman", 30.0f, juce::Font::bold | juce::Font::italic);
    g.setFont (mainComponentFont);

    // White text
    g.setColour (juce::Colours::white);
    g.drawText ("Learning JUCE", 20, 40, 200, 40, juce::Justification::centred, true);
    
    // Green line (5 px)
    g.setColour (juce::Colours::green);
    g.drawLine (10, 300, 590, 300, 5);
    
    // Brown line (3 px)
    g.setColour (juce::Colours::lime);
    g.drawLine (100, 200, 300, 300, 3);
    
    // Rectangle
    juce::Rectangle<float> house (300, 120, 200, 170);
    g.setColour (juce::Colours::sandybrown);
    
    g.fillCheckerBoard (house, 30, 10, juce::Colours::sandybrown, juce::Colours::saddlebrown);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
