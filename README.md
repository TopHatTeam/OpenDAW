# OpenDAW
A Open Source Digital Audio Workstation

### What platforms does this support?

Currently it supports

- Linux
- Windows

### Will MacOS support come?

Unlikely I don't own a Mac... Apple doesn't give SDKs out for people like me.

### Why use a BSD Clause 3 license?

This is suppose to be a blueprint for DAW developers. They can use this code freely without publicizing their work. This can be used for educational purposes, etc

### What are the features?

- **CD Support**
- **Audio Mainframe**
- **VST Support** (Coming soon)

### Is there going to be rust support

No, not low-level enough. Many of the dependencies use C/C++ not rust. That and the fact is that I'm not a great rust programmer so no... but you can rewrite this in rust if you're insane. I don't judge ;)

### Technology

- **Languages**: C/C++
- **GUI Toolkit**: GTK 4.0
- **Audio Backend (Linux)**: ALSA

### Dependencies

- GTK 4.0 (upgraded from 2.0) 
- ALSA (Linux)


### Ubuntu / Debian packages
```
sudo apt install libgtk4-dev
```

### Fedora / RedHat packages
```
sudo dnf install gtk4-devel
```

### Arch packages
```
sudo pacman -S gtk4
```

### MSYS2
```
pacman -S mingw-w64-x86_64-gtk4
```