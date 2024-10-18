
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