#include <queue.h>

int enqueue(QUEUE *queue)
{
    NODE *newNode = initNode();

    if (queue->size == 0)
    {
        queue->firstNode = newNode;
        queue->lastNode = newNode;
        queue->size = 1;
    }
    else
    {
        queue->lastNode->nextNode = newNode;
        queue->lastNode = newNode;
        queue->size++;
    }

    return 0;
}

int dequeue(QUEUE *queue)
{
    /* Special cases if queue is empty or if there's only one elem */
    if (queue->size == 0)
    {
        return 1;
    }
    if (queue->size == 1)
    {
        unsigned int wait = queue->firstNode->waitTime;

        NODE *removedNode = queue->firstNode;

        /* Empty queue */
        queue->firstNode = NULL;
        queue->lastNode = NULL;

        free(removedNode);

        queue->size = 0;

        return wait;
    }

    unsigned int wait = queue->firstNode->waitTime;

    NODE *removedNode = queue->firstNode;

    queue->firstNode = queue->firstNode->nextNode;

    free(removedNode);

    queue->size--;

    return wait;
}

int incrementWaits(QUEUE *queue)
{
    if (queue->size == 0)
    {
        return 1;
    }

    NODE *currentNode = queue->firstNode;
    currentNode->waitTime++;

    while (currentNode->nextNode != NULL)
    {
        currentNode = currentNode->nextNode;
        currentNode->waitTime++;
    }

    return 0;
}

int printWaits(QUEUE *queue)
{
    if (queue->size == 0)
    {
        return 1;
    }

    NODE *currentNode = queue->firstNode;

    unsigned int count = 1;

    while (currentNode->nextNode != NULL)
    {
        printf("Node %d waited %d\n", count, currentNode->waitTime);
        currentNode = currentNode->nextNode;
        count++;
    }

    return 0;
}

QUEUE *initQueue()
{
    QUEUE *queue = NULL;
    if ((queue = (QUEUE *)malloc(sizeof(QUEUE))) == NULL)
    {
        printf("Out of memory!\n");
        exit(1);
    }
    queue->firstNode = NULL;
    queue->lastNode = NULL;
    queue->size = 0;
    return queue;
}

NODE *initNode()
{
    NODE *node = NULL;
    if ((node = (NODE *)malloc(sizeof(NODE))) == NULL)
    {
        printf("Out of memory!\n");
        exit(1);
    }
    node->nextNode = NULL;
    node->waitTime = 0;
    return node;
}