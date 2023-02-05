
#include <runSimulations.h>

int main()
{
    /*Declaring parameter variables*/
    int lar, llp, rar, rlp;
    
    /*Declaring and initialising Variables for individual Simulation
     *and sum of individual simulations*/
    INFORETURN leftTotal, rightTotal;
    resetData(&leftTotal);
    resetData(&rightTotal);
   
    INFORETURN lData,rData;
    INFORETURN *ld = &lData;
    INFORETURN *rd = &rData;
  
    /*Get Paramter Values as input from User*/
    importResults(&lar, &llp, &rar, &rlp);
    
    /*Setup and seed random number generator*/
    const gsl_rng_type *T;
    gsl_rng *r;
    gsl_rng_env_setup();
    T = gsl_rng_default;
    r = gsl_rng_alloc(T);

    gsl_rng_set(r,time(0));

    /*Run the Simulation 100 times using the user inputted parameters*/  
    int i = 0;
    for(i=0;i<=100;i++)
    {
        resetData(ld);
        resetData(rd);        
        
        runSim(lar, llp, rar, rlp, ld, rd, r);
        updateTotal(&leftTotal, ld);
        updateTotal(&rightTotal, rd);
    }
    
    /*Output the initial Parameter values back to user*/
    printf("Parameter Values:\n");
    printf("    from left:\n");
    printf("        traffic arrival rate: %d%% \n", lar);
    printf("        traffic light period: %d \n", llp);
    printf("    from right:\n");
    printf("        traffic arrival rate: %d%%\n", rar);
    printf("        traffic light period: %d \n", rlp);
    printf("Results (Averaged over 100 runs):\n");
    printf("   from left:\n");
    printf("       average vehicles passed:%03.3f \n",(float)leftTotal.vehicles / (float)100 );
    printf("       average waiting time:   %03.3f \n",(float)leftTotal.wait / (float)100 );
    printf("       average max wait time:  %03.3f \n", (float)leftTotal.maxWait / (float)100);
    printf("       average clearance time: %03.3f \n", (float)leftTotal.clearance / (float)100);
    printf("   from right:\n");
    printf("       average vehicles passed:%03.3f \n", (float)rightTotal.vehicles / (float)100 );
    printf("       average waiting time:   %03.3f \n", (float)rightTotal.wait / (float)100);
    printf("       average max wait time:  %03.3f \n", (float)rightTotal.maxWait / (float)100);
    printf("       average clearance time: %03.3f \n", (float)rightTotal.clearance / (float)100);
    
    /*Freeing Memory allocated to gsl random generator*/
    gsl_rng_free(r);
    return EXIT_SUCCESS;
}

/*Takes user input to set parameter variables*/
void importResults(int *lar, int *llp, int *rar, int *rlp)
{
    printf("Enter 4 integers each seperated by a space, they should follow the");
    printf(" format the follows:\nLeft-Arrival Rate, Left Light Period, ");
    printf("Right-Arrival Rate, Right Light Phase. \n");
    if(!scanf("%d %d %d %d", lar, llp, rar, rlp))
    {
        fprintf(stderr,"Incorrect inputs were assigned to initial parameters \n");
        exit(1);
    }
    
}

/*Takes the values from individual simulation and appends to
 *  total value to allow for averages to be taken*/
void updateTotal(INFORETURN *totals, INFORETURN *singles)
{
    totals->vehicles = totals->vehicles + singles->vehicles;
    totals->wait = totals->wait + singles->wait;
    totals->maxWait = totals->maxWait + singles->maxWait;
    totals->clearance = totals->clearance + singles->clearance;
}

