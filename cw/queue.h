#include <stdio.h>
#include <stdlib.h>

struct node
{
    unsigned int waitTime;
    struct node *nextNode;
};
typedef struct node NODE;

struct queue
{
    struct node *firstNode;
    struct node *lastNode;
    unsigned int size;
    struct stats *statistics;
};
typedef struct queue QUEUE;

struct stats
{
    unsigned int totalVehicles;
    unsigned int totalWait;
    unsigned int maxWait;
    unsigned int timeToClear;
};
typedef struct stats STATS;

extern int enqueue(QUEUE *queue);
extern int dequeue(QUEUE *queue);
extern int incrementWaits(QUEUE *queue);
extern int printWaits(QUEUE *queue);
extern int printStats(QUEUE *queue);
static float avgWait(STATS *statistics);

extern QUEUE *initQueue();
static NODE *initNode();
static STATS *initStats();