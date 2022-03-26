#include <runSimulations.h>

STATPAIR *runOneSimulation(float leftFlow, float rightFlow, int leftTime, int rightTime)
{
    /* RNG setup */
    const gsl_rng_type *T;
    gsl_rng *r;
    gsl_rng_env_setup();
    T = gsl_rng_default;
    r = gsl_rng_alloc(T);

    gsl_rng_set(r, time(0));

    /* Initializing each queue */
    QUEUE *leftQueue = initQueue(leftQueue);

    QUEUE *rightQueue = initQueue(rightQueue);

    /* Keeping track of simulation parameters */
    /* Which light is green */
    char rightGreen;
    char leftGreen;
    /* How long until light turns red */
    unsigned int timeTillLeftRed;
    unsigned int timeTillRightRed;
    unsigned int remainingIterations = 500;
    unsigned int totalIterations = 1;

    /* Determining which light is on to begin with */
    if (gsl_ran_flat(r, 0, 1) < 0.5)
    {
        leftGreen = 0;
        rightGreen = 1;
        timeTillLeftRed = -1;
        timeTillRightRed = rightTime;
    }
    else
    {
        leftGreen = 1;
        rightGreen = 0;
        timeTillRightRed = -1;
        timeTillLeftRed = leftTime;
    }

    /* Stats for left */
    unsigned int totalLeftCars = 0;
    float avgLeftWait = 0;
    unsigned int maxLeftWait = 0;
    unsigned int timeToClearLeft = 0;

    /* Stats for right */
    unsigned int totalRightCars = 0;
    float avgRightWait = 0;
    unsigned int maxRightWait = 0;
    unsigned int timeToClearRight = 0;

    while (remainingIterations != 0 || (leftQueue->size != 0 || rightQueue->size != 0))
    {
        /* Possibility 1: Lights flipping */
        if (timeTillLeftRed == 0)
        {
            rightGreen = 1;
            leftGreen = 0;
            timeTillRightRed = rightTime;
            timeTillLeftRed--;
        }
        else if (timeTillRightRed == 0)
        {
            rightGreen = 0;
            leftGreen = 1;
            timeTillLeftRed = leftTime;
            timeTillRightRed--;
        }
        /* Possibility 2: Cars move */
        else
        {
            /* Step 1: Queue on left */
            if (gsl_ran_flat(r, 0, 1) < leftFlow && (remainingIterations != 0))
            {
                enqueue(leftQueue);
                totalLeftCars = totalLeftCars + 1;
            }

            /* Step 2: Queue on right */
            if (gsl_ran_flat(r, 0, 1) < rightFlow && (remainingIterations != 0))
            {
                enqueue(rightQueue);
                totalRightCars = totalRightCars + 1;
            }

            /* Step 3: Cars moving */
            if (leftGreen == 1 && leftQueue->size != 0)
            {
                dequeue(leftQueue);
            }
            else if (rightGreen == 1 && rightQueue->size != 0)
            {
                dequeue(rightQueue);
            }

            /* Iteration over; one step closer to flip */
            timeTillRightRed--;
            timeTillLeftRed--;
        }

        /* Step 4: Are cars done arriving? */
        if (remainingIterations != 0)
        {
            remainingIterations--;
        }
        else
        {
            if (rightQueue->size != 0)
            {
                /* Stat logging (time to empty the queue) */
                rightQueue->statistics->timeToClear++;
            }
            if (leftQueue->size != 0)
            {
                /* Stat logging (time to empty the queue) */
                leftQueue->statistics->timeToClear++;
            }
        }

        /* Incrementing all the time parameters */
        totalIterations++;
        incrementWaits(leftQueue);
        incrementWaits(rightQueue);
    }

    /* Get stats into pairs and release memory */
    STATPAIR *results = createPair(leftQueue->statistics, rightQueue->statistics);

    free(rightQueue);
    free(leftQueue);

    return results;
}

int runSimulations(float leftFlow, float rightFlow, int leftTime, int rightTime){
    int i;

    STATS *avgLeft = initStats();
    STATS *avgRight = initStats();

    for(i = 0; i<100; i++){
        STATPAIR *currentPair = (STATPAIR *)runOneSimulation(0.5, 0.5, 3, 3);

        avgLeft->totalVehicles += currentPair->left->totalVehicles;
        avgLeft->totalWait += currentPair->left->totalWait;
        avgLeft->timeToClear += currentPair->left->timeToClear;
        if(currentPair->left->maxWait > avgLeft->maxWait){
            avgLeft->timeToClear = currentPair->left->maxWait;
        }

        free(currentPair->left);

        avgRight->totalVehicles += currentPair->right->totalVehicles;
        avgRight->totalWait += currentPair->right->totalWait;
        avgRight->timeToClear += currentPair->right->timeToClear;
        if(currentPair->right->maxWait > avgRight->maxWait){
            avgRight->timeToClear = currentPair->right->maxWait;
        }

        free(currentPair->right);

        free(currentPair);
    }

    printf(
        "Parameter values:\n
            from left:\n
                traffic arrival rate: %.3f\n
                traffic light period: %3d\n
            from right:\n
                traffic arrival rate: %.3f\n
                traffic light period: %3d\n
        Results (Averaged over 100 runs):\n
            from left:\n
                number of vehicles: %.3f\n
                average waiting time: %.3f\n
                maximum waiting time: %d\n
                clearance time: %.3f\n
            from right:\n
                number of vehicles: %.3f\n
                average waiting time: %.3f\n
                maximum waiting time: %d\n
                clearance time: %.3f\n
                ",
                
    )
}

int main()
{
    STATPAIR *x = (STATPAIR *)runOneSimulation(0.5, 0.5, 3, 3);

    printStats1(x->left);
    printStats1(x->right);

    return 0;
}