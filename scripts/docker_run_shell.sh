#!/bin/bash
set -e

IMAGE_NAME="team14_project"
TAG="0.1.0"

echo "http://localhost:8080"

docker run -it --rm \
  -p 8080:8080 \
  "$IMAGE_NAME:$TAG" bash