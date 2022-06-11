#!/bin/bash
echo "Stopping container..."
docker stop ipc

echo "Removing container..."
docker rm ipc
echo "Container removed."
docker ps -a