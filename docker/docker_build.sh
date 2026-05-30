#!/bin/bash
set -e

PROJECT_ROOT="$(dirname "$0")/.."
cd "$PROJECT_ROOT"

IMAGE_NAME="team14_game"
TAG="latest"

echo "▶ Docker image build start..."
docker build -f docker/Dockerfile -t "$IMAGE_NAME:$TAG" .

echo ""
echo "build complete : $IMAGE_NAME:$TAG"
echo ""