#include <stdio.h>
#include <stdlib.h>

struct node
{
    unsigned int waitTime;
    struct node *nextNode;
};
typedef struct node NODE;

int enqueue(NODE *root);
int dequeue(NODE *root);
int incrementWaits(NODE *root);