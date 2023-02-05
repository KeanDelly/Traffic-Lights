
#include <runOneSimulation.h>

void runSim(long lar, long llp, long rar, long rlp, INFORETURN *leftData, INFORETURN *rightData, gsl_rng *r)
{
    /*Declaring and initialising light tracker and counter variables*/
    int llpt = 0;   
    int rlpt = 0;  
    char lpt = 'l';
    
    /*Declaring and initialising the left and right hand queues*/
    QUEUE *lRoot = NULL;
    QUEUE *rRoot = NULL;
    
    /*Declaring and initialising wait time temp variable and waittime sum counter*/
    int waitTime;
    int lWaitTimeTotal = 0;
    int rWaitTimeTotal = 0;
  
    /*Starting simulation with initial loop in which cars can arrive for first 500 periods*/
    unsigned short int i = 0;
    
    for(i;i<=500;i++)
    {
        /*Check whether the Lights need to change sides based
         *on thier respective light period tracker*/
        if (llp == llpt && lpt == 'l')
        {
            lpt = 'r';
            i++;
            rlpt = 0;
        }

        if (rlp == rlpt && lpt == 'r')
        {
            lpt = 'l';
            i++;
            llpt = 0;
        }

        
        /*Based on a random number generator, Determine wether a car arrves at left, 
         *then right and add to respective queue if so.*/
        if (genRand(lar, r))
        {
            if(lRoot == NULL)
                lRoot = newNode(i);
            else
                Push(i, lRoot);
            leftData->vehicles++;
        }

        if (genRand(rar, r))
        {
            if(rRoot == NULL)
                rRoot = newNode(i);
            else
                Push(i, rRoot);
            rightData->vehicles++;
        }

   
        /*Depending on which side of the lights are 'green',
         *if the corresponding queue is not empty then pop one element from
         *that queue and storing its data*/
        if(lpt == 'l' && (!(lRoot == NULL)))
        {
            waitTime = i - lRoot->arrivalPeriod;
            lWaitTimeTotal = lWaitTimeTotal + waitTime;            
            if (leftData->maxWait < waitTime )
                leftData->maxWait = waitTime;
            Pop(&lRoot);
        }
        if(lpt == 'r' && (!(rRoot == NULL)))
        {
            int waitTime = i - rRoot->arrivalPeriod;
            rWaitTimeTotal = rWaitTimeTotal + waitTime; 
            if(rightData->maxWait < waitTime )
                rightData -> maxWait = waitTime;
            Pop(&rRoot);
        }

        /*Increment the Light Trackers*/
        if(lpt == 'l')
            llpt++;
        else
            rlpt++;
    }
    

    /*Begin second part of the simulation in which no more 'cars' arrive
     *this continues until both left and right queues are empty */
    while((!(lRoot == NULL)) || (!(rRoot == NULL)))
    {
        /*check whether the Lights need to change, if so change lights and
         *increment the time period counter */
       	if (llp == llpt && lpt == 'l')
        {
            lpt = 'r';
            i++;
            rlpt = 0;
        }
        if (rlp == rlpt && lpt == 'r')
        {
            lpt = 'l';
            i++;
            llpt = 0;
        }

        /*Check if lights alight to left*/
        if(lpt == 'l')
        {
            /*If queue is not empty, pop first element of left queue and process data*/
            if(!(lRoot == NULL))
            {
                waitTime= i- lRoot->arrivalPeriod;
                lWaitTimeTotal = lWaitTimeTotal + waitTime;            
                if(leftData->maxWait < waitTime)
                    leftData -> maxWait = waitTime;
                Pop(&lRoot);
            }
            else /*If queue is empty*/
            {
                if(leftData->clearance == 0)/*If clearance time marker not set*/
                    leftData->clearance = i;/*Set clearance time*/
            }
        }

        /*Check if lights alight to right*/
        if(lpt == 'r')
        {
            /*If queue is not empty, pop front element of list and process its data*/
            if(!(rRoot == NULL))
            {
                waitTime = i-  rRoot->arrivalPeriod;
                rWaitTimeTotal = rWaitTimeTotal + waitTime;
                if(rightData->maxWait < waitTime)
                    rightData -> maxWait = waitTime;
                Pop(&rRoot);
            }
            else/*If queue is empty*/
            {
                if(rightData->clearance == 0)/*If Clearance Time not set*/
                    rightData->clearance = i; /*Set clearance time*/
            }
        }

        /*Increment Light time period Trackers*/
        if(lpt == 'l')
            llpt++;
        else
            rlpt++;
        i++;
    }
    
    /*Calculate the average wait time for both queues*/
    leftData->wait =(float)lWaitTimeTotal / (float)leftData->vehicles;
    rightData->wait = (float)rWaitTimeTotal / (float)rightData->vehicles;
    
    /*assert that final clearance marker was set*/
    if(rightData->clearance == 0)
        rightData->clearance = i;
    if(leftData->clearance == 0)
        leftData->clearance = i;

}

/*Takes the Arrival Rate Parameter to produce a True or False Event*/
int genRand(unsigned short int arp, gsl_rng *r)
{
    unsigned short int randNum = gsl_ran_flat(r,0,100);
    if (randNum <= arp)
    {    
        return 1;
    }
    else
    {
        return 0; 
    }
}

/*Rstores the data store back to default values of 0*/
void resetData(INFORETURN *data)
{
    data->vehicles = 0;
    data->wait = 0;
    data->maxWait = 0;
    data->clearance = 0;
}
