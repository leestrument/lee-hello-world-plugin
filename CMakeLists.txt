cmake_minimum_required(VERSION 3.22)

project(AUDIO_PLUGIN_EXAMPLE VERSION 0.0.1)

set(PRODUCT_NAME "HelloWorld")

include(FetchContent)

FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG master 
)

FetchContent_Declare(
    webview2
    URL "https://www.nuget.org/api/v2/package/Microsoft.Web.WebView2"
    DOWNLOAD_NO_PROGRESS TRUE
    SOURCE_DIR
    "${CMAKE_BINARY_DIR}/_deps/Microsoft.Web.WebView2"
)

FetchContent_MakeAvailable(JUCE webview2)

set(JUCE_WEBVIEW2_PACKAGE_LOCATION "${CMAKE_BINARY_DIR}/_deps")

juce_add_plugin(${PRODUCT_NAME}
    BUNDLE_ID "dev.helloworld.plugin"
    COMPANY_NAME "HelloWorld"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT TRUE
    AU_MAIN_TYPE kAudioUnitType_MIDIProcessor
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE hlwr
    PLUGIN_CODE Hlwr
    FORMATS AU VST3 Standalone
    PRODUCT_NAME ${PRODUCT_NAME}
    NEEDS_WEB_BROWSER TRUE
    NEEDS_WEBVIEW2 TRUE
)

juce_generate_juce_header(${PRODUCT_NAME})

target_sources(${PRODUCT_NAME} PRIVATE main.cpp)

target_compile_definitions(${PRODUCT_NAME}
    PUBLIC
        JUCE_WEB_BROWSER=1
        JUCE_USE_WIN_WEBVIEW2_WITH_STATIC_LINKING=1
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(${PRODUCT_NAME}
    PRIVATE
        juce::juce_audio_utils
        juce::juce_gui_extra
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)