#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

int runOneSimulation(float leftFlow, float rightFlow, int leftTime, int rightTime);


int runOneSimulation(float leftFlow, float rightFlow, int leftTime, int rightTime)
{
    unsigned int leftQueue = 0;
    unsigned int rightQueue = 0;

    const gsl_rng_type *T;
    gsl_rng *r;
    gsl_rng_env_setup();
    T = gsl_rng_default;
    r = gsl_rng_alloc(T);

    gsl_rng_set(r, time(0));

    char rightOn;
    char leftOn;

    /* Determining which light is on to begin with */
    if (gsl_ran_flat(r, 0, 1) < 0.5)
    {
        leftOn = 0;
        rightOn = 1;
    }
    else
    {
        leftOn = 1;
        rightOn = 0;
    }

    unsigned int remainingIterations = 500;
    unsigned int timeTillLeftFlip = leftTime;
    unsigned int timeTillRightFlip = rightTime;

    while (remainingIterations != 0 && (leftQueue != 0 || rightQueue != 0))
    {
        /* Step 1: Queue on left */
        if (gsl_ran_flat(r, 0, 1) < leftFlow)
        {
            leftQueue = leftQueue + 1;
        }
        /* Step 2: Queue on right */
        if (gsl_ran_flat(r, 0, 1) < rightFlow)
        {
            rightQueue = rightQueue + 1;
        }
        /* Step 3: Cars move */
        if (leftOn == 1 && leftQueue != 0)
        {
            leftQueue = leftQueue - 1;
        }
        if (rightOn == 1 && rightQueue != 0)
        {
            rightQueue = rightQueue - 1;
        }

        /* Step 4: flipping traffic lights if necessary */
        if (timeTillLeftFlip == 0)
        {
            if (leftOn == 1)
                leftOn = 0;
            else
                leftOn = 1;
            timeTillLeftFlip = leftTime;
        }
        else
            timeTillLeftFlip--;

        if (timeTillRightFlip == 0)
        {
            if (rightOn == 1)
                rightOn = 0;
            else
                rightOn = 1;
            timeTillRightFlip = rightTime;
        }
        else
            timeTillRightFlip--;
        
        remainingIterations--;
    }

    return 0;
}

int main()
{

    printf("hello.txt");

    return 0;
}