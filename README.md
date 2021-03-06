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
**Notice:** If you get errors about missing dll files - please install the latest Microsoft Visual C++ Redistributable from https://support.microsoft.com/en-hk/help/2977003/the-latest-supported-visual-c-downloads  
  
AnyBarWin consists of 2 parts: `AnyBarWin` - server and `AnyBarWinClient` - client    
To start using simply type in your favorite terminal `AnyBarWinClient <icon_name>` where `<icon_name>` is one of the available images: transparent, white, red, green, blue, question, exclamation, orange, yellow, purple, black, cyan  
To see list of available commands run client without arguments  


**Notice:** For now, the only available icon format is .ico

## Details
The app is using named pipes from WinApi. You can find auto-generated documentation by doxygen in `doc\html\index.html`

## Changes log
#### 02.07.2019 v1.1  
Changes:
- Added new command "start" which starts the server  
- Added new icons to availables list  
- Added more verbose error messages 


##### 26.06.2019 v1.0  
Initial version

