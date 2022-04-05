
<h1 align="center">
Bomberman
<br>
<br>
  <a href="" rel="noopener">
 <img src="" alt="Bomberman"></a>
</h1>

[![wakatime](https://wakatime.com/badge/user/65beb3fe-edbf-47a9-a9dc-9253600acc77/project/f86ee28f-1f22-4b44-91e0-9047f56bde1d.svg)](https://wakatime.com/badge/user/65beb3fe-edbf-47a9-a9dc-9253600acc77/project/f86ee28f-1f22-4b44-91e0-9047f56bde1d)
[![Latest Github release](https://img.shields.io/github/release/nicolapreda/bomberman.svg)](https://img.shields.io/github/release/nicolapreda/bomberman.svg)
[![Build status of the master branch on Linux/OSX](https://img.shields.io/travis/Martinsos/edlib/master?label=Linux%20%2F%20OSX%20build)](https://travis-ci.com/Martinsos/edlib)
[![Build status of the master branch on Windows](https://img.shields.io/appveyor/build/Martinsos/edlib/master?label=Windows%20build)](https://ci.appveyor.com/project/Martinsos/edlib/branch/master)
[![Chat on Gitter](https://img.shields.io/gitter/room/Martinsos/edlib.svg?colorB=753a88)](https://gitter.im/Martinsos/edlib)
[![Published in Bioinformatics](https://img.shields.io/badge/Published%20in-Bioinformatics-167DA4.svg)](https://doi.org/10.1093/bioinformatics/btw753)


 A remake created by @nicolapreda of Bomberman official game with C/C++ and SFML library.

Author:
* [nicolapreda](https://github.com/nicolapreda)
## Features


## Contents
- [About](#about)
- [Getting Started](#getting_started)
- [Deployment](#deployment)
- [Usage](#usage)
- [Built Using](#built_using)
- [Authors](#authors)
- [Acknowledgments](#acknowledgement)


## Using Bomberman in your project
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See [deployment](#deployment) for notes on how to deploy the project on a live system.

Clone this repository with web interface or via git command:

```bash
git clone https://github.com/diskxo/bantumi
```

and save it into your local workspace.

## Prerequisites

#### Windows

- [SFML 2.5.1 - GCC 7.3.0 MinGW (DW2) 32-bit (for Windows)](https://www.sfml-dev.org/files/SFML-2.5.1-windows-gcc-7.3.0-mingw-32-bit.zip)
- [GCC 7.3.0 MinGW (DW2) 32-bit (for Windows)](https://downloads.sourceforge.net/project/mingw-w64/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/7.3.0/threads-posix/dwarf/i686-7.3.0-release-posix-dwarf-rt_v5-rev0.7z?ts=gAAAAABiCPISZlK6KeJPFkS8_Njt5-hapDJK8HRnt_RnH-rFaZAX1xCODdbRhImYmibYQkervhYczQM9d5dzqgzLkXMObiYChg%3D%3D&r=https%3A%2F%2Fsourceforge.net%2Fprojects%2Fmingw-w64%2Ffiles%2FToolchains%2520targetting%2520Win32%2FPersonal%2520Builds%2Fmingw-builds%2F7.3.0%2Fthreads-posix%2Fdwarf%2Fi686-7.3.0-release-posix-dwarf-rt_v5-rev0.7z%2Fdownload)
- [Git Bash (for Windows) ](https://git-scm.com/downloads)

#### MacOS

- [SFML 2.5.1 - Clang 64-bit](https://www.sfml-dev.org/files/SFML-2.5.1-macOS-clang.tar.gz)
- Command Line Tools / XCode (type "xcode-select --install" in terminal to trigger the installer)

#### Linux

- Get SFML 2.5.1 from your distro if it has it, or compile from source

#### All

- [Visual Studio Code](https://code.visualstudio.com/download)
- Extensions (install from Extensions panel):
  - [Official C/C++ Extension (0.21.0+)](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
  - [Shader languages support for VS Code (Optional Syntax Highlighting)](https://marketplace.visualstudio.com/items?itemName=slevesque.shader)
  - [x86 and x86_64 Assembly (Optional Syntax Highlighting)](https://marketplace.visualstudio.com/items?itemName=13xforever.language-x86-64-assembly)
  - [Studio Icons (Optional Icon Theme)](https://marketplace.visualstudio.com/items?itemName=jtlowe.vscode-icon-theme)

---

## Installing

#### Windows

1. Download & Extract SFML to **C:/SFML-2.5.1/** where the bin/lib/include folders are contained within
2. Download & Extract MinGW to **C:/mingw32/** where the bin/lib/include folders are contained within

#### MacOS

1. Install "Command Line Tools" in MacOS if they're not already installed (type "xcode-select --install" in terminal)
2. Follow the "Installing SFML" directions here: https://www.sfml-dev.org/tutorials/2.5/start-osx.php#installing-sfml

#### Linux

1. Ensure the GCC Toolchain is installed

```bash
sudo apt install build-essential
```

or

```bash
sudo pacman -S base-devel
```

2. Install libsfml

```bash
sudo apt install libsfml-dev
```

or

```bash
sudo pacman -S sfml
```

The SFML version you got will vary depending on the distro. 2.5.1 is included in [Ubuntu 19.04 Disco Dingo](http://cdimage.ubuntu.com/daily-live/current/HEADER.html) for example.

#### All

1. Download & Install Visual Studio Code if you don't already have it.
2. Install the official **C/C++** Extension, reload the window & wait for the dependencies to install.
3. If on Windows, install **Git Bash**, and ensure the **"terminal.integrated.shell.windows"** property in the project's **settings.json** is set to **bash.exe**'s correct location (default: C:/Program Files/Git/bin/bash.exe). We'll be using this for the terminal in our workspace so that the Makefile can run in both Windows, Mac & Linux
4. In **settings.json** Ensure **Path** in the **terminal.integrated.env.windows** object is set to the correct location of the compiler's executable (example: C:\\mingw32\\bin) and the SFML directory is correct as well. Keep in mind Paths should be separated by a semi-colon with no spaces between.

**Note:** You can manage the "Path" environment variable from Windows if you'd like, but I've found sandboxing it in VS Code is better for tracking things like .dll dependencies.

---