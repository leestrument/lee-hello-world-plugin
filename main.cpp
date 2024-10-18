#include <JuceHeader.h>

struct HelloWorldProcessor : juce::AudioProcessor
{
    HelloWorldProcessor(): AudioProcessor (BusesProperties ()
    #if ! JucePlugin_IsMidiEffect
    #if ! JucePlugin_IsSynth
        .withInput  ("Input",  juce::AudioChannelSet::stereo (), true)
    #endif
        .withOutput ("Output", juce::AudioChannelSet::stereo (), true)
    #endif
    ){}

    ~HelloWorldProcessor() override {}

    void prepareToPlay (double, int) override {}
    void releaseResources() override {}

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override
    {
        #if JucePlugin_IsMidiEffect
            juce::ignoreUnused (layouts);
            return true;
        #else
            if (layouts.getMainOutputChannelSet () != juce::AudioChannelSet::mono ()
            && layouts.getMainOutputChannelSet () != juce::AudioChannelSet::stereo ())
                return false;

        #if ! JucePlugin_IsSynth
            if (layouts.getMainOutputChannelSet () != layouts.getMainInputChannelSet ())
                return false;
        #endif
            return true;
        #endif
    }

    void processBlock (juce::AudioBuffer<float>& audio, juce::MidiBuffer&) override 
    {
        audio.clear ();
    }

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return "HelloWorld"; }

    bool acceptsMidi () const override
    {
        #if JucePlugin_WantsMidiInput
            return true;
        #else
            return false;
        #endif
    }

    bool producesMidi () const override
    {
        #if JucePlugin_ProducesMidiOutput
            return true;
        #else
            return false;
        #endif
    }

    bool isMidiEffect () const override
    {
        #if JucePlugin_IsMidiEffect
            return true;
        #else
            return false;
        #endif
    }
    
    
    double getTailLengthSeconds() const override { return 0.0; }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram (int) override {}
    const juce::String getProgramName (int) override { return {}; }
    void changeProgramName (int, const juce::String&) override {}

    void getStateInformation (juce::MemoryBlock&) override {}
    void setStateInformation (const void*, int) override {}
};

struct HelloWorldEditor : juce::AudioProcessorEditor
{
    HelloWorldProcessor& processor;
    juce::WebBrowserComponent browser
    {
        juce::WebBrowserComponent::Options {}
        .withBackend (juce::WebBrowserComponent::Options::Backend::webview2)
        .withWinWebView2Options (WebBrowserComponent::Options::WinWebView2{}.withUserDataFolder (File::getSpecialLocation (File::SpecialLocationType::tempDirectory)))
    };

    HelloWorldEditor (HelloWorldProcessor& p)
        : AudioProcessorEditor (p), processor (p)
    {   
        addAndMakeVisible (browser);
        browser.goToURL ("https://google.com");
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
        browser.setBounds (getLocalBounds ());
    }
};

juce::AudioProcessorEditor* HelloWorldProcessor::createEditor()
{
    return new HelloWorldEditor (*this);
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HelloWorldProcessor();
}