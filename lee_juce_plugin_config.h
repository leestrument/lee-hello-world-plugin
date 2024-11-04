#pragma once
#include <JuceHeader.h>

/* 
    플러그인 창 크기라던지, 플러그인이 다크 모드이던지
    daw state 가 아닌, plugin 모든 instance 에 적용될 global state 를 저장하기위한 클래스
    내부적으로 juce::PropertiesFile 를 사용하여, 사용자의 컴퓨터에 데이터를 저장하고 불러옴.

    createPluginPropertiesOptions ("config") 를 하며 xml 파일이 파일명.config 로 생성
    mac 에서는 Macintosh HD/Users/사용자이름/Library/Application Support/회사이름/플러그인이름/플러그인이름.config
    주의할점은 사용자이름안에 Library 폴더는 숨김폴더이므로 Finder 에서 보이지않아, 보이게 할려면 cmd + shift + . 를 눌러야함.

    < 참고한 코드들 >
    https://github.com/trackbout/ripchord/blob/9958125ac2e829215018856a2be19b667daaee80/Source/PluginEditor.cpp#L21
    https://github.com/trackbout/ripchord/blob/9958125ac2e829215018856a2be19b667daaee80/Source/Modules/System.h#L35
*/

struct LeeJucePluginConfig
{   
    juce::PropertiesFile configFile;

    LeeJucePluginConfig (const juce::String& filenameSuffix = "config"): configFile (createOptions (filenameSuffix))
    {}
    
    juce::PropertiesFile::Options createOptions (const juce::String& filenameSuffix)
    {
        juce::PropertiesFile::Options options;
        
        options.applicationName = JucePlugin_Name;
        options.folderName = juce::File::addTrailingSeparator (JucePlugin_Manufacturer) + JucePlugin_Name;
        options.filenameSuffix = filenameSuffix;
        options.osxLibrarySubFolder = "Application Support";
        options.commonToAllUsers = false;
        options.ignoreCaseOfKeyNames = true;
        options.doNotSave = false;
        options.millisecondsBeforeSaving = 10;
        options.storageFormat = juce::PropertiesFile::storeAsXML;
        
        return options;
    }

    void storeBounds (const juce::Rectangle<int>& bounds)
    {
        setValue ("width",  bounds.getWidth  ());
        setValue ("height", bounds.getHeight ());
    }

    bool hasStoredBounds () const
    {
        return getValueAsInt ("width") > 0 && getValueAsInt ("height") > 0;
    }

    double getWidth  () const { return getValueAsDouble ("width"); }
    double getHeight () const { return getValueAsDouble ("height"); }

    void setValue (const juce::String& key, const juce::var& value)
    {
        configFile.setValue (key, value);
        configFile.saveIfNeeded ();
    }

    void setValue (const juce::String& key, float value)
    {
        setValue (key, juce::var (value));
    }

    void setValue (const juce::String& key, int value)
    {
        setValue (key, juce::var (value));
    }

    juce::var getValue (const juce::String& key, const juce::var& fallback = juce::var ()) const
    {
        return configFile.getValue (key, fallback);
    }

    int getValueAsInt (const juce::String& key, int fallback = 0) const
    {
        return configFile.getValue (key, juce::var (fallback)).getIntValue ();
    }

    float getValueAsFloat(const juce::String& key, float fallback = 0.0f) const
    {
        return configFile.getValue (key, juce::var (fallback)).getFloatValue ();
    }

    double getValueAsDouble (const juce::String& key, double fallback = 0.0) const
    {
        return configFile.getValue (key, juce::var (fallback)).getDoubleValue ();
    }
};