#!/bin/bash

touch file 
echo "1" > file

# Copy data to docker using tee
docker exec -i button tee /tmp/button < file > /dev/null