#include <runSimulations.h>

int runOneSimulation(float leftFlow, float rightFlow, int leftTime, int rightTime)
{
    /* RNG setup */
    const gsl_rng_type *T;
    gsl_rng *r;
    gsl_rng_env_setup();
    T = gsl_rng_default;
    r = gsl_rng_alloc(T);

    gsl_rng_set(r, time(0));

    /* Keeping track of simulation parameters */
    /* Queue Sizes */
    unsigned int leftQueue = 0;
    unsigned int rightQueue = 0;
    /* Which light is green */
    char rightGreen;
    char leftGreen;
    /* How long until light turns red */
    unsigned int timeTillLeftRed;
    unsigned int timeTillRightRed;
    unsigned int remainingIterations = 500;

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

    while (remainingIterations != 0 || (leftQueue != 0 || rightQueue != 0))
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
                leftQueue = leftQueue + 1;
                totalLeftCars = totalLeftCars + 1;
            }

            /* Step 2: Queue on right */
            if (gsl_ran_flat(r, 0, 1) < rightFlow && (remainingIterations != 0))
            {
                rightQueue = rightQueue + 1;
                totalRightCars = totalRightCars + 1;
            }

            /* Step 3: Cars moving */
            if (leftGreen == 1 && leftQueue != 0)
            {
                leftQueue = leftQueue - 1;
            }
            else if (rightGreen == 1 && rightQueue != 0)
            {
                rightQueue = rightQueue - 1;
            }

            timeTillRightRed--;
            timeTillLeftRed--;
        }

        /* Step 4: Are cars done arriving? */
        if (remainingIterations != 0)
            remainingIterations--;

        printf("remainingiterations: %d. rightGreen = %d. leftGreen = %d. leftQueue = %d, rightQueue = %d\n", remainingIterations, rightGreen, leftGreen, leftQueue, rightQueue);
    }
    return 0;
}

int main()
{

    /* runOneSimulation(0.9, 0.9, 3, 3); */

    NODE *root = NULL;

    if ((root = (NODE *)malloc(sizeof(NODE))) == NULL)
    {
        printf("Out of memory!\n");
        exit(1);
    }
    else
    {
        enqueue(root);
        enqueue(root);
        enqueue(root);
        enqueue(root);
        enqueue(root);


        dequeue(&root);


        unsigned int count = countNodes(root);

        printf("Number of nodes in queue: %d\n",count);
    }

    return 0;
}