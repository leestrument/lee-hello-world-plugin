#pragma
#include <JuceHeader.h>

namespace lee
{
    juce::Array<juce::File> findFiles (const juce::File& directory, const juce::String& extension)
    {
        return directory.findChildFiles (juce::File::findFiles, false, "*." + extension);
    }

    juce::var parseJSONFile (const juce::File& file)
    {
        return juce::JSON::parse (file.loadFileAsString ());
    }

    juce::File getCommonDocumentsDirectory ()
    {
        return juce::File::getSpecialLocation (juce::File::commonDocumentsDirectory);
    }

    juce::File getUserDataPath (const juce::String& inCompanyName, const juce::String& inAppName)
    {
        #if JUCE_MAC || JUCE_IOS
            juce::File directory ("~/Library/");
            directory = directory.getChildFile ("Application Support");
        #elif JUCE_LINUX || JUCE_ANDROID
            const File directory ("~");
        #elif JUCE_WINDOWS
            File directory (File::getSpecialLocation (File::userApplicationDataDirectory));
        #endif

        return directory.getChildFile (inCompanyName).getChildFile (inAppName);
    }
}