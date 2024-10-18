#include <JuceHeader.h>

//--------------------------------------------------------------------------------------------------
class HelloWorldProcessor : public juce::AudioProcessor
{
public:
    HelloWorldProcessor()
        #if JucePlugin_Enable_ARA
             : AudioProcessor (BusesProperties()
                                .withInput  ("Input",  juce::AudioChannelSet::stereo())
                                .withOutput ("Output", juce::AudioChannelSet::stereo()))
        #else
             : AudioProcessor (BusesProperties()
                                .withInput  ("Input",  juce::AudioChannelSet::stereo())
                                .withOutput ("Output", juce::AudioChannelSet::stereo()))
        #endif
    {
    }

    ~HelloWorldProcessor() override {}

    void prepareToPlay (double sampleRate, int samplesPerBlock) override {}
    void releaseResources() override {}

    void processBlock (juce::AudioBuffer<float>& audio, juce::MidiBuffer&) override 
    {
        audio.clear ();
    }

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return "HelloWorld"; }

    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram (int) override {}
    const juce::String getProgramName (int) override { return {}; }
    void changeProgramName (int, const juce::String&) override {}

    void getStateInformation (juce::MemoryBlock&) override {}
    void setStateInformation (const void*, int) override {}

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelloWorldProcessor)
};

//--------------------------------------------------------------------------------------------------
class HelloWorldEditor : public juce::AudioProcessorEditor
{
public:
    HelloWorldEditor (HelloWorldProcessor& p)
        : AudioProcessorEditor (p), processor (p)
    {   
        addAndMakeVisible (webBrowserComponent);
        webBrowserComponent.goToURL ("https://google.com");
        setSize (500, 500);
    }

    ~HelloWorldEditor() override {}

    void paint (juce::Graphics& g) override
    {
        g.fillAll (juce::Colours::black);
        g.setColour (juce::Colours::white);
        g.setFont (20.0f);
        g.drawText ("Hello World", getLocalBounds(), juce::Justification::centred, true);
    }

    void resized () override 
    {
        webBrowserComponent.setBounds (getLocalBounds ());
    }

private:
    HelloWorldProcessor& processor;
    juce::WebBrowserComponent webBrowserComponent 
    {
        juce::WebBrowserComponent::Options {}
        .withBackend (juce::WebBrowserComponent::Options::Backend::webview2)
        .withWinWebView2Options (WebBrowserComponent::Options::WinWebView2{}.withUserDataFolder (File::getSpecialLocation (File::SpecialLocationType::tempDirectory)))
    };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelloWorldEditor)
};

juce::AudioProcessorEditor* HelloWorldProcessor::createEditor()
{
    return new HelloWorldEditor (*this);
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HelloWorldProcessor();
}