#include <stdio.h>
#include <stdlib.h>

struct node
{
    unsigned int waitTime;
    struct node *nextNode;
};
typedef struct node NODE;

extern int enqueue(NODE **root);
extern int dequeue(NODE **root);
extern int incrementWaits(NODE *root);
extern int printWaits(NODE *root);
extern int countNodes(NODE *root);