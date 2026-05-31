#!/bin/bash
set -e

IMAGE_NAME="team14_project"
TAG="demo"

echo "▶ Detecting Operating System for Docker GUI Forwarding..."

# Windows (WSL2)
if [ -f /proc/version ] && grep -qi microsoft /proc/version; then
    echo "OS Detected: Windows (WSL2)"
    echo "Launching game in Docker..."
    docker run -it --rm \
      -e DISPLAY=$DISPLAY \
      -v /tmp/.X11-unix:/tmp/.X11-unix \
      "$IMAGE_NAME:$TAG" bash

# macOS
elif [[ "$OSTYPE" == "darwin"* ]]; then
    echo "OS Detected: macOS"
    echo "Ensuring XQuartz access..."
    xhost +localhost
    echo "Launching game in Docker..."
    docker run -it --rm \
      -e DISPLAY=host.docker.internal:0 \
      "$IMAGE_NAME:$TAG" bash

# Linux
elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
    echo "OS Detected: Linux"
    echo "Enabling local docker display access..."
    xhost +local:docker
    echo "Launching game in Docker (with GPU Access)..."
    docker run -it --rm \
      -e DISPLAY=$DISPLAY \
      -v /tmp/.X11-unix:/tmp/.X11-unix \
      --device /dev/dri \
      "$IMAGE_NAME:$TAG" bash

# 4. Windows (Git Bash)
elif [[ "$OSTYPE" == "msys" || "$OSTYPE" == "cygwin" ]]; then
    echo "OS Detected: Windows (Git Bash)"
    echo "Ensure VcXsrv (XLaunch) is running with 'Disable access control' checked!"

    IP=$(powershell.exe -Command "(Get-NetIPAddress -InterfaceAlias 'vEthernet (WSL)' | Select-Object -First 1).IPAddress" 2>/dev/null | tr -d '\r')
    if [ -z "$IP" ]; then
        IP=$(ipconfig.exe | grep -i "IPv4" | head -n 1 | awk -F': ' '{print $2}' | tr -d '\r')
    fi
    
    echo "🚀 Launching game targeting XServer at $IP..."
    docker run -it --rm \
      -e DISPLAY="${IP}:0" \
      "$IMAGE_NAME:$TAG" bash

else
    echo "Unknown OS type ($OSTYPE). Trying default docker run..."
    docker run -it --rm "$IMAGE_NAME:$TAG" bash
fi