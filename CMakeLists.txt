cmake_minimum_required(VERSION 3.22)

project(HelloWorld VERSION 0.0.1)

include(FetchContent)

FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG origin/master
    GIT_SHALLOW ON
)

if (WIN32)

    # 윈도우에서 c++ runtime 을 static 하게 link 하기 위한 설정
    # 이 라인이 없어서 태형컴에서 열자마자 계속 crash 가 발생함.
    # crash 가 발생안한 사람들의 컴퓨터의 이유는 어떠한 다른 경로로 c++ runtime 이 설치된 경우임.
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    
    set(CMAKE_GENERATOR_PLATFORM "x64")
    
    # 윈도우 WebView2 를 사용하기 위한 설정
    FetchContent_Declare(
        webview2
        URL "https://www.nuget.org/api/v2/package/Microsoft.Web.WebView2"
        DOWNLOAD_NO_PROGRESS TRUE
        SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/Microsoft.Web.WebView2"
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    
    set(JUCE_WEBVIEW2_PACKAGE_LOCATION "${CMAKE_BINARY_DIR}/_deps")
    
    FetchContent_MakeAvailable(webview2)
    
elseif (APPLE)

    # mac 에서 최소 버전을 10.14 로 설정
    # 이거 안하면 구형 intel mac 에서 scan 이 안됨.
    # 이거 설정안하면 컴파일 한 컴퓨터의 버전으로 최소 버전이 설정됨.
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.14" CACHE STRING "Minimum OS X deployment version" FORCE) 

    # intel mac 과 새로운 mac 둘다 돌아가기위한 Universal Binary 를 만들기 위한 설정
    set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")

endif()

FetchContent_MakeAvailable(JUCE)

# nlohmann/json 라이브러리 설정 (develop 브랜치 사용)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG develop  # develop 브랜치를 사용
)

FetchContent_MakeAvailable(nlohmann_json)

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
    FORMATS Standalone

     # 윈도우 WebView2 를 사용하기 위한 설정
    NEEDS_WEB_BROWSER TRUE
    NEEDS_WEBVIEW2 TRUE
)

juce_add_binary_data(BinaryData SOURCES "index.html")

juce_generate_juce_header(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE main.cpp)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC
        # 윈도우 WebView2 를 사용하기 위한 설정
        JUCE_WEB_BROWSER=1
        JUCE_USE_WIN_WEBVIEW2_WITH_STATIC_LINKING=1
        
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        BinaryData
        juce::juce_audio_utils
        nlohmann_json::nlohmann_json  # nlohmann/json 라이브러리 추가
    PUBLIC
        # 이거 없으면 mac 에서 binary size 가 2배로 증가함.. 8~9메가 나와야하는데, 16메가가 되버림.
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
