# ***Better AltTab for Starfield***
[![C++23](https://img.shields.io/static/v1?label=standard&message=C%2B%2B23&color=blue&logo=c%2B%2B&&logoColor=white&style=flat)](https://en.cppreference.com/w/cpp/compiler_support)
[![Latest Release](https://img.shields.io/github/release/epinter/better-alttab-sf.svg)](https://github.com/epinter/better-alttab-sf/releases/latest)
[![Downloads](https://img.shields.io/github/downloads/epinter/better-alttab-sf/total.svg)](https://github.com/epinter/better-alttab-sf/releases/latest)
[![Release Date](https://img.shields.io/github/release-date/epinter/better-alttab-sf.svg)](https://github.com/epinter/better-alttab-sf/releases/latest)
[![License](https://img.shields.io/github/license/epinter/better-alttab-sf.svg)](https://github.com/epinter/better-alttab-sf/blob/main/LICENSE)

A simple mod show cursor when mouse is over the windowed game.

## ***Runtime requirements***

- [Starfield Script Extender (SFSE)](https://sfse.silverlock.org/)
- [Address Library for SFSE Plugins](https://www.nexusmods.com/starfield/mods/3256)
- [Latest VC++ Redist](https://learn.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist)

## ***Build requirements***

- [CMake](https://cmake.org/)
- [vcpkg](https://vcpkg.io/en/)
- [Visual Studio Community 2022](https://visualstudio.microsoft.com/vs/community/)
- [CommonLibSSF](https://github.com/Starfield-Reverse-Engineering/CommonLibSF)

## ***Building***

In `Developer PowerShell for VS`, run:

~~~
git clone https://github.com/epinter/better-alttab-sf.git
cd better-alttab-sf
~~~

then

~~~
.\cmake\build.ps1
~~~

or

~~~
.\cmake\build.ps1 -buildPreset default
~~~

or

~~~
.\cmake\build.ps1 -buildPreset debug -configPreset default -toolset v143
~~~

Then get the .dll in build/bin/Release, or the .zip (ready to install using mod manager) in build.