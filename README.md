# Simple Guitar Tuner
A guitar tuner for Linux or Windows that detects frequencies between 60 and 1060 Hz. Building is done on a Linux machine. ./bin/tuner is for Linux, ./bin/tuner.exe is the Windows executable.

To compile you need the raylib and miniaudio as dependancies. `miniaudio.h` is included in the include folder. Follow the instructions for raylib, for Linux and Windows respectively.

### Linux:

Full instructions are here: [raylib github linux](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux)

`sudo apt install build-essential git cmake`

Ubuntu
```sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev```

Fedora
`sudo dnf install alsa-lib-devel mesa-libGL-devel libX11-devel libXrandr-devel libXi-devel libXcursor-devel libXinerama-devel libatomic`

Arch Linux
`sudo pacman -S alsa-lib mesa libx11 libxrandr libxi libxcursor libxinerama`

Void Linux
`sudo xbps-install make alsa-lib-devel libglvnd-devel libX11-devel libXrandr-devel libXi-devel libXcursor-devel libXinerama-devel mesa MesaLib-devel`

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
In the root folder run `make linux`

### Windows

Full instructions are here: [raylib github windows](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux)

`sudo apt install g++-mingw-w64-x86-64 gcc-mingw-w64-x86-64`

Build raylib
```
mkdir lib && cd lib
mkdir raylib-windows && cd raylib-windows
wget https://github.com/raysan5/raylib/releases/download/5.5/raylib-5.5_win64_mingw-w64.zip
unzip raylib-5.5_win64_mingw-w64.zip
rm raylib-5.5_win64_mingw-w64.zip
```
In the root folder run `make windows`
