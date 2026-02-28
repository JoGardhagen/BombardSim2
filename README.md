# BombardSim2
# System Deps
```bash
sudo apt update && sudo apt install -y \
cmake git build-essential \
libx11-dev libxcursor-dev libxinerama-dev libxrandr-dev libxi-dev \
libasound2-dev libgl-dev libglu1-mesa-dev libwayland-dev \
libxkbcommon-dev xwayland
```
### To Run Raspberry pi 
```bash
export DISPLAY=:0
LIBGL_ALWAYS_SOFTWARE=1 ./bin/BombardSim
```