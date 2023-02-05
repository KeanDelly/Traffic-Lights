
#include <stdio.h>
#include <stdlib.h>
#include <util_queue.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

/*Defining the structure to runturn data from individual simulation to the overall*/
struct returnStruct 
{
    unsigned short int vehicles;
    float wait;
    unsigned short int maxWait;
    int clearance;
};

typedef struct returnStruct INFORETURN;

/*Function Prototypes*/
void runSim(long, long, long, long, INFORETURN*, INFORETURN*, gsl_rng*);
int genRand(unsigned short int, gsl_rng*);
void resetData(INFORETURN*);
