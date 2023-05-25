#!/bin/bash

cd ./lib/sala_reto
gcc sala_reto.c -c
cd ../
ar -crs libsalareto.a sala_reto/sala_reto.o
cd ../fuentes
gcc test_sala_reto.c -o tsr -lsalareto -L../lib
./tsr
