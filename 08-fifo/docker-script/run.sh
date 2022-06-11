#!/bin/bash

IP=$1

if [ "$IP" = "" ]; then 
    echo "Usage: ./run <ip_machine>"
    echo "e.g: ./run 192.168.0.1"
    exit 1
fi

docker run -itd --log-driver syslog --log-opt syslog-address=tcp://$IP:514 --name ipc ipcs