

##COMPILING THE PROGRAM
To compile the program you can either;

1.run 'compileSim' in the folder

2.run the following commands in consecutive order:
    gcc -ansi -I./ -c util_queue.c -o util_queue.o
    gcc -ansi -I./ -c runOneSimulation.c -o runOneSimulation.o
    gcc -ansi -I./ -c runSimulations.c -o runSimulations.o
    gcc runSimulations.o runOneSimulation.o util_queue.o -lgsl -lgslcblas -o runSimulations





##RUNNING THE PROGRAM
When running the program, you will be asked for an input for initial parameters of the form:
Left Arrival Rate, Left Light Period, Right Arrival Rate, Right Light Period.

Both Arrival rate parameters should be integers between 1-100. 
Both Light Period parameters can be any positive integer greater than 0.

Your input should be space seperated like so;
EXAMPLE INPUT: 50 5 50 5

