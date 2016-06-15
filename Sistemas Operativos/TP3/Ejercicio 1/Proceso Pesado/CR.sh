#!/bin/bash

gcc -w -I.. Caso1.c ../utils.c -o c1
gcc -w -I.. Caso2.c ../utils.c -o c2

xterm -hold -T "Caso 1" -e "./c1"
xterm -hold -T "Caso 2" -e "./c2"

rm "./c1"
rm "./c2"