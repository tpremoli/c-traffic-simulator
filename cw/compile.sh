gcc -ansi -c runSimulations.c -o runSimulations.o
gcc runSimulations.o -lgsl -lgslcblas -o runSimulations
./runSimulations
