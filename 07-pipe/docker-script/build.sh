#!/bin/bash

echo "Generating image ..."
cd ..
docker build -t pipes .
docker image ls | grep pipes

echo "Done!"