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

    return 0;
}

int main()
{

    printf("hello.txt");

    return 0;
}