#pragma once
#include <JuceHeader.h>

/* 
    https://docs.juce.com/master/classFile.html
    https://github.com/trackbout/ripchord/blob/9958125ac2e829215018856a2be19b667daaee80/Source/Modules/System.h#L35

    userDocumentsDirectory 
    userApplicationDataDirectory 
    commonDocumentsDirectory 
    commonApplicationDataDirectory 
*/
struct LeeJuceFileManager
{
    juce::PropertiesFile mTagsFile      { createPluginPropertiesOptions ("tags") };
    juce::PropertiesFile mFavoritesFile { createPluginPropertiesOptions ("favorites") };
    juce::PropertiesFile mConfigFile    { createPluginPropertiesOptions ("config") };

    LeeJuceFileManager ()
    {
        createDirectory (getCommonDocumentsDirectory (), { "LEESTRUMENT", "CHORDimist", "Presets" });
        testJucePropertiesFiles ();
    }

    void testJucePropertiesFiles ()
    {
        mConfigFile.setValue ("theme", 1);
        mConfigFile.saveIfNeeded ();
    }

    juce::File getCommonDocumentsDirectory ()
    {
        return juce::File::getSpecialLocation (juce::File::commonDocumentsDirectory);
    }

    void openFolder (const juce::File& f)
    {
        if (f.isDirectory ()) f.revealToUser ();
    }

    void openLEESTRUMENTFolder ()
    {
        openFolder (getCommonDocumentsDirectory ().getChildFile ("LEESTRUMENT"));
    }

    void createDirectory (const juce::File& parent, const std::initializer_list<juce::String>& folders)
    {
        juce::File current = parent;

        for (const auto& folder : folders)
        {
            current = current.getChildFile (folder);
            current.createDirectory ();  // 이미 존재할 경우 아무 일도 일어나지 않음
        }
    }

    // https://github.com/trackbout/ripchord/blob/9958125ac2e829215018856a2be19b667daaee80/Source/Modules/System.h#L35
    juce::PropertiesFile::Options createPluginPropertiesOptions (const String& inFilenameSuffix)
    {
        juce::PropertiesFile::Options pluginPropertiesOptions {};
        
        pluginPropertiesOptions.applicationName = "CHORDimist";
        pluginPropertiesOptions.folderName = File::addTrailingSeparator ("LEESTRUMENT") + "CHORDimist";
        pluginPropertiesOptions.filenameSuffix = inFilenameSuffix;
        pluginPropertiesOptions.osxLibrarySubFolder = "Application Support";
        pluginPropertiesOptions.commonToAllUsers = false;
        pluginPropertiesOptions.ignoreCaseOfKeyNames = true;
        pluginPropertiesOptions.doNotSave = false;
        pluginPropertiesOptions.millisecondsBeforeSaving = 10;
        pluginPropertiesOptions.storageFormat = PropertiesFile::storeAsXML;
        
        return pluginPropertiesOptions;
    }
};