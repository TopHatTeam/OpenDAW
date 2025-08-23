<img src="assets/logo.png" width="300">

# OpenDAW

A Open Source Digital Audio Workstation

### What platforms does this support?

Currently it supports

- Linux
- Windows
- MacOS

### Will MacOS support come?

~~Unlikely I don't own a Mac... Apple doesn't give SDKs out for people like me.~~

I found a way to make MacOS support and that involves using a virtual machine to get the SDKs.. "**shhh** don't tell Tim Cook"

### Why use a BSD Clause 3 license?

This is suppose to be a blueprint for DAW developers. They can use this code freely without publicizing their work. This can be used for educational purposes, etc.
Also don't use my name to promote your custom DAW. That's jus not cool

### What are the features?

- **CD Support**    
- **Midi Support** (Currently in development)
- **Audio Mainframe**   
- **VST Support** (Coming soon)
- **Support for targets without C library support**

### Is there going to be rust support

No, not low-level enough. Many of the dependencies use C/C++ not rust. That and the fact is that I'm not a great rust programmer so no... but you can rewrite this in rust if you're insane. I don't judge ;)

I may use rust for specific drivers stuff that requires security and safety.
So rust is not fully off the table

### Technology

- **Languages**: C/C++, Rust, Objective-C++
- **GUI Toolkit**: ImGui
- **Audio Backend (Linux)**: ALSA

### Dependencies

- ImGui &rarr; For the graphical user interface
- ALSA &rarr; For Linux audio backend
- Rust &rarr; For specific memory and logic safety areas
- fmt &rarr; For a bloat-free and fast c++ library
- SDL3 &rarr; For making the window
- rtmidi &rarr; For implementing the MIDI functionality
- libsndfile &rarr; For exporting and importing sound formats 


### Ubuntu / Debian packages

```bsh
sudo apt install build-essential libburn-dev cmake make clang clang++ libvulkan-dev
```

Optional installs

```bash
sudo apt install python3
```

### Fedora / RedHat packages

```bash
sudo dnf install gtk4-devel
```

### Arch packages

```bash
sudo pacman -S gtk4
```

### MSYS2

```bash
pacman -S mingw-w64-x86_64-gtk4
```

# Compiling on Windows

### install dependencies

```bash
pacman -S mingw-w64-x86_64-pkgconf make cmake
```

If you want to make the icon 

```bash
pacman -S mingw-w64-x86_64-icoutils
```

Now to do follow the following steps to get this to work
- Go to search and type, **System Environment Variables**
- Click on **Edit the system environment variables**
- Then a **System Properties** window will popup. Underneath **Startup and Recovery** there is a button that says **Environment Variables...** click on that button.
- Go to the **System variables** section and click on **Path** and above **Ok** and **Cancel** click on the button that says **Edit...**. Click on that button
- Then a **Edit environment variable** window will popup. On the right there's a button that says **New**. Click on that button and type this &rarr; **C:\msys64\mingw64\bin**
- Hit enter, then click **OK** on both windows
- You will need to close and reopen your coding editor for this to work. Then look at the *How to create the icon?* for further information

### Now compiling

```bash
cd /path/to/OpenDAW
mkdir build
cd build
cmake -G "MinGW Makefiles" -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Release ..
mingw32-make
```

### How to create the icon?

Run the python script for your specific Operating System

- **MacOS** &rarr; create_icon_mac.py
- **Windows** &rarr; create_icon_win.py