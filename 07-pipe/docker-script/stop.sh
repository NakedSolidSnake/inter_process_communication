#!/bin/bash
echo "Stopping container..."
docker stop pipe

echo "Removing container..."
docker rm pipe
echo "Container removed."
docker ps -a