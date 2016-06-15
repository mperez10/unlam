#!/bin/bash

gcc -I.. procesoA.c ../utils.c -o pa
gcc -I.. procesoB.c ../utils.c -o pb

xterm -hold -T "Proceso A" -e "./pa" &
sleep 2
xterm -hold -T "Proceso B" -e "./pb"

rm "./pa"
rm "./pb"