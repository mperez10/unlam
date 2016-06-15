#!/bin/bash

gcc -I.. server.c ../utils.c -o server
gcc -I.. client.c ../utils.c -o client

xterm -hold -T "Servidor" -e "./server" &
sleep 2
xterm -hold -T "Cliente" -e "./client"

rm "./server"
rm "./client"