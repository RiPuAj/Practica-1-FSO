#!/bin/bash

cd ./lib/sala
gcc sala.c -c
cd ../
ar -crs libsala.a sala/sala.o
cd ../fuentes
gcc test_sala.c -o ts -lsala -L../lib
./ts
