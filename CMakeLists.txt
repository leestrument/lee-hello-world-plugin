cmake_minimum_required(VERSION 3.22)

project(HelloWorld VERSION 0.0.1)

# 이 라인이 없으면, Windows 의 DAW 에서 scan 되지 않습니다... 
# 이 라인이 없어서, 몇몇 사람들의 컴퓨터에서 열자마자 crash 가 발생하였었습니다.
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

include(FetchContent)

FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG origin/master
    GIT_SHALLOW ON
)

FetchContent_Declare(
    webview2
    URL "https://www.nuget.org/api/v2/package/Microsoft.Web.WebView2"
    DOWNLOAD_NO_PROGRESS TRUE
    SOURCE_DIR
    "${CMAKE_BINARY_DIR}/_deps/Microsoft.Web.WebView2"
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(JUCE webview2)

set(JUCE_WEBVIEW2_PACKAGE_LOCATION "${CMAKE_BINARY_DIR}/_deps")

set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")

if (WIN32)
    set(CMAKE_GENERATOR_PLATFORM "x64")
endif()

juce_add_plugin(${PROJECT_NAME}
    PRODUCT_NAME ${PROJECT_NAME}
    BUNDLE_ID "dev.leestrument.plugin"
    COMPANY_NAME "LEESTRUMENT"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT TRUE
    AU_MAIN_TYPE kAudioUnitType_MIDIProcessor
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE Lees
    PLUGIN_CODE Lee1
    FORMATS AU VST3 Standalone
    NEEDS_WEB_BROWSER TRUE
    NEEDS_WEBVIEW2 TRUE
)

juce_generate_juce_header(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE main.cpp)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC
        JUCE_WEB_BROWSER=1
        JUCE_USE_WIN_WEBVIEW2_WITH_STATIC_LINKING=1
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        juce::juce_audio_utils
)
