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
};
typedef struct queue QUEUE;

extern int enqueue(QUEUE *queue);
extern int dequeue(QUEUE *queue);
extern int incrementWaits(QUEUE *queue);
extern int printWaits(QUEUE *queue);
extern QUEUE *initQueue();
extern NODE *initNode();