#!/bin/bash

touch file 
echo "1" > file

# Copy data to docker using tee
docker exec -i pipe tee /tmp/pipe < file > /dev/null