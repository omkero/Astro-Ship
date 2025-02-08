cmake -S . -B build/

# For debug 
cmake --build build/ --config Debug

# For Release
cmake --build build/ --config Release

# run
./build/release/sdl_gui.exe

for linux you have to install this libraries

!! required !!

# Install SDL2 and SDL2_ttf
sudo apt-get install libsdl2-dev libsdl2-ttf-dev

# Install SDL2_image
sudo apt-get install libsdl2-image-dev

(optional only if you use opengl)

# Install OpenGL development libraries
sudo apt-get install libgl-dev

# Install GLEW (if using OpenGL extensions)
sudo apt-get install libglew-dev
