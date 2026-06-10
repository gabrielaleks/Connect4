# Connect4

![logo](assets/logo.svg)

A Connect4 game built in C++ with Qt6, supporting local two-player and online multiplayer modes.

## Requirements

- Qt 6.5 or later (with Svg, SvgWidgets, and Network components)
- CMake 3.19 or later
- A C++17 compiler

## Building

The easiest way is to open `CMakeLists.txt` in Qt Creator and use the built-in build/run buttons. Alternatively, build from the command line:

**macOS**
```bash
cmake -B build -DCMAKE_PREFIX_PATH=~/Qt/6.11.1/macos
cmake --build build
```

**Windows** (adjust the Qt path to match your installation)
```bash
cmake -B build -DCMAKE_PREFIX_PATH=C:\Qt\6.11.1\msvc2022_64
cmake --build build
```

## Running

### Local mode

Launch the app, enter player names and colors on the config screen, and click Play.

### Online mode

1. One machine runs the relay server (separate project, provided by the instructor). When it starts, it displays its IP address and listens on port **12345**.
2. Both machines launch Connect4, check **Online mode** on the config screen, enter the server's IP address, and select their role (Player 1 or Player 2).
3. Click Play on both instances to start.

## Distributing

To produce a self-contained build that runs without Qt installed:

**macOS**
```bash
~/Qt/6.11.1/macos/bin/macdeployqt build/Connect4.app
```
Then zip and share the `.app` bundle.

**Windows**
```bash
C:\Qt\6.11.1\msvc2022_64\bin\windeployqt build\Connect4.exe
```

Then zip and share the folder containing `Connect4.exe` and the deployed Qt files.
