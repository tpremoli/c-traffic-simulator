gcc -ansi -I ./ -c runSimulations.c -o runSimulations.o
gcc -ansi -I ./ -c queue.c -o queue.o
gcc runSimulations.o queue.o -lgsl -lgslcblas -o runSimulations
./runSimulations
