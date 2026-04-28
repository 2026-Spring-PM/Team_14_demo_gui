#!/bin/bash
set -e
cd "$(dirname "$0")/.."
docker build -f docker/Dockerfile -t team14_game:latest .
echo "docker image build done"