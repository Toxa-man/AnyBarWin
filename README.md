# AnyBarWin
Client-server app that allows you to change icons in tray

## Building
In order to build the solution you would need MS Visual Studio Ver. >= 2017 with compiller that supports C++17  
1. Clone repository from https://github.com/Toxa-man/AnyBarWin  
2. Open `.sln` file from root folder
3. Build the required target using Visual Studio  

Or alternatively you can use Native Tools Command Promt for VS  
1. Find and run Native Tools Command Promt for VS
2. Change directory to repository root
3. At the command prompt, type `MSBuild`

**Notice:** You will also need Google Tests Adapter in order to build tests. You can download it using NuGet or Visual Studio Installer. 

## Using
**Notice:** If you get errors about missing ucrtbased.dll or VCRUNTIME.dll - please, install the latest Microsoft Visual C++ Redistributable from https://support.microsoft.com/en-hk/help/2977003/the-latest-supported-visual-c-downloads  
  
AnyBarWin consists of 2 parts: `AnyBarWin` - server and `AnyBarWinClient` - client    
To start using application first run server and then change icons by using client from command prompt  
To see list of available commands run client without arguments  


**Notice:** For now, thy only available icon format is .ico

## Details
The app is using named pipes from WinApi. You can find auto-generated documentation by doxygen in `doc\html\index.html`
