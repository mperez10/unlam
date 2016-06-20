#!/bin/bash

gcc -w -I.. Caso3.c ../utils.c -o c3 -pthread
gcc -w -I.. Caso4.c ../utils.c -o c4 -pthread

xterm -hold -T "Caso 3" -e "taskset -c 0 ./c3"
xterm -hold -T "Caso 4" -e "taskset -c 0 ./c4"

rm "./c3"
rm "./c4"
