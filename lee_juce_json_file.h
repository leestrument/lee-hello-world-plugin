#pragma once
#include <JuceHeader.h>
#include <nlohmann/json.hpp>
#include <string>

/*
    CMakeLists 에 nlohmann_json 이 반드시 추가되어야합니다. 파일을 열어 확인하세요.

    https://forum.juce.com/t/construct-var-programmatically-and-convert-to-json/7958/6

    juce::File 은 진짜 file 이 아니고, file 을 가리키는 포인터일 뿐임.
    실제 파일이 생성되는 경우는 file 이 제대로된 경로를 가졌고, replaceWithText 를 호출했을 때임.
    이 클래스는 컴퓨터 폴더에 있는 json 파일과 연결시키고, juce 에서 이를 로딩,수정하기위한 클래스임.
*/

struct LeeJuceJSONFile
{
    nlohmann::json json {};
    juce::File file {};

    LeeJuceJSONFile () = default;

    LeeJuceJSONFile (const juce::File& f) { setFile (f); }

    void test ()
    {   
        setFile (juce::File::getSpecialLocation (juce::File::commonDocumentsDirectory).getChildFile ("test.json"));
        setProperty ("test", juce::Random::getSystemRandom ().nextFloat ());
    }

    void setProperty (const std::string& key, const nlohmann::json& value)
    {
        json [key] = value;
        saveToRealFile ();
    }

    void removeProperty (const std::string& key)
    {   
        // crash 는 안나지만, saveToRealFile 를 굳이 호출하게하지않기위해서임.
        if (json.contains (key))
        {
            json.erase (key);
            saveToRealFile ();
        }
    }

    void setFile (const juce::File& f)
    {
        file = f;
        loadFromRealFile ();
    }

    void loadFromRealFile ()
    {   
        // 이거 check 안하면 crash 남. 아마 file.loadFileAsString () 때문인듯.
        if (file.existsAsFile ()) json = nlohmann::json::parse (file.loadFileAsString ().toStdString ());
    }

    void saveToRealFile ()
    {   
        // replaceWithText 를 호출하면 파일이 없을 경우 생성해줌.
        file.replaceWithText (json.dump ());
    }

    juce::var toVar ()
    {
        return juce::JSON::parse (json.dump ());
    }
};