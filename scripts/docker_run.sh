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
      "$IMAGE_NAME:$TAG"

# macOS
elif [[ "$OSTYPE" == "darwin"* ]]; then
    echo "OS Detected: macOS"
    xhost +localhost
    docker run -it --rm \
      -e DISPLAY=host.docker.internal:0 \
      "$IMAGE_NAME:$TAG"

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
      "$IMAGE_NAME:$TAG"

else
    echo "Unavailable OS type ($OSTYPE). Please Try Again With WSL2 or MacOS or Linux"
fi
