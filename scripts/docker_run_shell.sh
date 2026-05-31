#!/bin/bash
set -e

IMAGE_NAME="team14_project"
TAG="0.1.0"

echo "▶ Detecting Operating System for Docker GUI Forwarding..."

# Windows (WSL2)
if [ -f /proc/version ] && grep -qi microsoft /proc/version; then
    echo "OS Detected: Windows (WSL2)"
    xhost +localhost
    docker run -it --rm \
      -e DISPLAY=$DISPLAY \
      -e PULSE_SERVER=unix:/mnt/wslg/PulseServer \
      -v /tmp/.X11-unix:/tmp/.X11-unix \
      -v /mnt/wslg:/mnt/wslg \
      "$IMAGE_NAME:$TAG" bash

# macOS
elif [[ "$OSTYPE" == "darwin"* ]]; then
    echo "OS Detected: macOS"
    xhost +localhost
    docker run -it --rm \
      -e DISPLAY=host.docker.internal:0 \
      "$IMAGE_NAME:$TAG" bash

# Linux
elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
    echo "OS Detected: Linux"
    xhost +local:docker
    
    docker run -it --rm \
      -e DISPLAY=$DISPLAY \
      -v /tmp/.X11-unix:/tmp/.X11-unix \
      --device /dev/dri \
      --device /dev/snd \
      --group-add audio \
      --ipc=host \
      "$IMAGE_NAME:$TAG" bash

# 4. Windows (Git Bash)
elif [[ "$OSTYPE" == "msys" || "$OSTYPE" == "cygwin" ]]; then
    echo "OS Detected: Windows (Git Bash)"

    IP=$(powershell.exe -Command "(Get-NetIPAddress -InterfaceAlias 'vEthernet (WSL)' | Select-Object -First 1).IPAddress" 2>/dev/null | tr -d '\r')
    if [ -z "$IP" ]; then
        IP=$(ipconfig.exe | grep -i "IPv4" | head -n 1 | awk -F': ' '{print $2}' | tr -d '\r')
    fi
    
    docker run -it --rm \
      -e DISPLAY="${IP}:0" \
      -v /mnt/wslg:/mnt/wslg \
      -e PULSE_SERVER=unix:/mnt/wslg/runtime-dir/pulse/native \
      --ipc=host \
      "$IMAGE_NAME:$TAG" bash

else
    echo "Unavailable OS type ($OSTYPE). Please Try Again With WSL2 or MacOS or Linux"
fi
