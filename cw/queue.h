#include <stdio.h>
#include <stdlib.h>

/* Each item in queue */
struct node
{
    unsigned int waitTime;
    struct node *nextNode;
};
typedef struct node NODE;

/* Queue itself */
struct queue
{
    struct node *firstNode;
    struct node *lastNode;
    unsigned int size;
    struct stats *statistics;
};
typedef struct queue QUEUE;

/* struct tracking stats */
struct stats
{
    unsigned int totalVehicles;
    unsigned int totalWait;
    unsigned int maxWait;
    unsigned int timeToClear;
};
typedef struct stats STATS;

/* Struct paired into one (left/right) */
struct statPair
{
    STATS *left;
    STATS *right;
};
typedef struct statPair STATPAIR;

/* Adds car to queue */
extern int enqueue(QUEUE *queue);

/* Removes car from queue */
extern int dequeue(QUEUE *queue);

/* Adds a timestep to the wait time */
extern int incrementWaits(QUEUE *queue);

/* Printing waits and stats (utility) */
extern int printWaits(QUEUE *queue);
extern int printStats(QUEUE *queue);
extern int printStats1(STATS *statistics);

/* Returns average wait time */
extern float avgWait(STATS *statistics);


/* Turns pair of stats into statpair struct */
extern STATPAIR *createPair(STATS* left, STATS* right);

/* Initializes empty queue */
extern QUEUE *initQueue();

/* Initializes empty node */
static NODE *initNode();

/* Initialises empty stats */
extern STATS *initStats();
