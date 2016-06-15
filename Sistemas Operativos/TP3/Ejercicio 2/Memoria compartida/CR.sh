#!/bin/bash

gcc -w -I.. procesoA.c ../utils.c -o pa -lpthread
gcc -w -I.. procesoB.c ../utils.c -o pb -lpthread

xterm -hold -T "Proceso A" -e "./pa" &
sleep 2
xterm -hold -T "Proceso B" -e "./pb"

rm "./pa"
rm "./pb"