#!/bin/bash
set -e

PROJECT_ROOT="$(dirname "$0")/.."
cd "$PROJECT_ROOT"

IMAGE_NAME="team14_project"
TAG="demo"

echo "▶ Docker image build start..."
docker build -f docker/Dockerfile --target demo -t "$IMAGE_NAME:$TAG" .

echo ""
echo "build complete : $IMAGE_NAME:$TAG"
echo ""