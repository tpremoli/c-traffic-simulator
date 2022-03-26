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

    /* Determining which light is on to begin with */
    if (gsl_rng_uniform_pos(r) < 0.5)
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
            if (gsl_rng_uniform_pos(r) < leftFlow && (remainingIterations != 0))
            {
                enqueue(leftQueue);
            }

            /* Step 2: Queue on right */
            if (gsl_rng_uniform_pos(r) < rightFlow && (remainingIterations != 0))
            {
                enqueue(rightQueue);
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
        incrementWaits(leftQueue);
        incrementWaits(rightQueue);
    }

    /* Get stats into pairs and release memory */
    STATPAIR *results = createPair(leftQueue->statistics, rightQueue->statistics);

    free(rightQueue);
    free(leftQueue);
    /* printf("%f\n",gsl_rng_uniform_pos(r)); */

    gsl_rng_free(r);

    return results;
}

int runSimulations(float leftFlow, float rightFlow, int leftTime, int rightTime)
{
    int i;

    STATS *avgLeft = initStats();
    STATS *avgRight = initStats();

    for (i = 0; i < 100; i++)
    {
        STATPAIR *currentPair = (STATPAIR *)runOneSimulation(leftFlow, rightFlow, leftTime, rightTime);

        avgLeft->totalVehicles += currentPair->left->totalVehicles;
        avgLeft->totalWait += currentPair->left->totalWait;
        avgLeft->timeToClear += currentPair->left->timeToClear;
        if (currentPair->left->maxWait > avgLeft->maxWait)
        {
            avgLeft->maxWait = currentPair->left->maxWait;
        }

        free(currentPair->left);

        avgRight->totalVehicles += currentPair->right->totalVehicles;
        avgRight->totalWait += currentPair->right->totalWait;
        avgRight->timeToClear += currentPair->right->timeToClear;
        if (currentPair->right->maxWait > avgRight->maxWait)
        {
            avgRight->maxWait = currentPair->right->maxWait;
        }

        free(currentPair->right);

        free(currentPair);
    }

    printf("Parameter values:\n");
    printf("\tfrom left:\n");
    printf("\t\ttraffic arrival rate: %.2f\n", leftFlow);
    printf("\t\ttraffic light period: %03d\n", leftTime);
    printf("\tfrom left:\n");
    printf("\t\ttraffic arrival rate: %.2f\n", rightFlow);
    printf("\t\ttraffic light period: %03d\n", rightTime);
    printf("Results (Averaged over 100 runs):\n");
    printf("\tfrom left:\n");
    printf("\t\tnumber of vehicles: %03d\n", avgLeft->totalVehicles / 100);
    printf("\t\taverage waiting time: %03d\n", (int)avgWait(avgLeft));
    printf("\t\tmaximum waiting time: %03d\n", avgLeft->maxWait);
    printf("\t\tclearance time: %03d\n", avgLeft->timeToClear / 100);
    printf("\tfrom right:\n");
    printf("\t\tnumber of vehicles: %03d\n", avgRight->totalVehicles / 100);
    printf("\t\taverage waiting time: %03d\n", (int)avgWait(avgRight));
    printf("\t\tmaximum waiting time: %03d\n", avgRight->maxWait);
    printf("\t\tclearance time: %03d\n", avgRight->timeToClear / 100);

    free(avgLeft);
    free(avgRight);

    return 0;
}

int main()
{
    runSimulations(0.15, 0.95, 2, 12);

    return 0;
}