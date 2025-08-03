# Simple Guitar Tuner
A guitar tuner for Linux or Windows that detects frequencies between 60 and 1060 Hz. Building is done on a Debian based Linux machine. ./bin/tuner is for Linux, ./bin/tuner.exe is the Windows executable.

To compile you need raylib and miniaudio as dependancies. `miniaudio.h` is included in the include folder. Follow the instructions for raylib, for Linux and Windows respectively.

### Linux version:

Full instructions are here: [raylib github linux](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux)

```
sudo apt install build-essential git cmake
sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
```

Build raylib using cmake
```
git clone https://github.com/raysan5/raylib.git lib/raylib-linux
cd lib/raylib-linux
mkdir build && cd build
cmake -DBUILD_SHARED_LIBS=ON ..
make
sudo make install
sudo ldconfig
```

### Windows version

Full instructions are here: [raylib github windows](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux)

`sudo apt install g++-mingw-w64-x86-64 gcc-mingw-w64-x86-64`

Build raylib
```
mkdir lib && cd lib mkdir raylib-windows && cd raylib-windows
wget https://github.com/raysan5/raylib/releases/download/5.5/raylib-5.5_win64_mingw-w64.zip
unzip raylib-5.5_win64_mingw-w64.zip
rm raylib-5.5_win64_mingw-w64.zip
```

### Compile tuner

In the root folder run `make linux` or `make windows`, dependant on your target system.
