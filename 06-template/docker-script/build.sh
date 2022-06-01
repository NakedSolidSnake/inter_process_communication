#!/bin/bash

echo "Generating image ..."
cd ..
docker build -t ipcs .
docker image ls | grep ipcs

echo "Done!"