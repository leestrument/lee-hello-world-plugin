< 목적 >
이 Hello Worl 앱은 Standalone 으로,
lee-juce 에 코드를 올리기전에, 먼저 프로토타이핑해보는 장소입니다.
dsp 보다는 native 코드와 관련된 것들이 대부분일것입니다. 파일시스템, 드래그엔드랍등..


< How to build ? >

Since I don't have a Windows computer, I build through GitHub Actions. 
When you commit the code, the build.yml is executed through GitHub Actions, 
and you can download the .vst3 file from the artifacts.
Please note that GitHub Actions is only free for public repositories, so you'll need to toggle that setting.

< FL Studio is unable to scan my plugin. >

There's an issue where the plugin is not being scanned in FL Studio, but this is no longer my fault.

1. The most important thing is that FL Studio does not support placing VST3 files in a custom folder. 
   You must place the VST3 file in the designated location on either Mac or Windows. 
2. You need to check "Verify plugins" and then click "Find Installed Plugins."

< Webview2 is not being used, and Internet Explorer continues to be used >

In Windows, you must ensure that Microsoft Edge browser is installed.

< It crashes as soon as it opens on the computer. >

To enable static C++ runtime linking in the CMakeList, you must add set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>").

https://discord.com/channels/382895736356077570/785560654484340747/1002350528682004571
https://discord.com/channels/382895736356077570/785560654484340747/1001363437261172796
https://discord.com/channels/382895736356077570/667185391006122015/1088872580825481307
https://forum.juce.com/t/important-breaking-change-juce-will-now-use-dynamic-linking-for-the-windows-runtime-by-default/25276
https://discord.com/channels/382895736356077570/382908951324262400/759062178522464258