#include <queue.h>

int enqueue(NODE *root)
{
    NODE *newNode;
    if ((newNode = (NODE *)malloc(sizeof(NODE))) == NULL)
    {
        printf("Out of memory!\n");
        exit(1);
    }
    else
    {
        NODE *currentNode = root;

        while (currentNode->nextNode != NULL)
        {
            currentNode = currentNode->nextNode;
        }

        newNode->waitTime = 0;
        newNode->nextNode = NULL;

        currentNode->nextNode = newNode;
    }

    return 0;
}

int countNodes(NODE *root)
{
    unsigned int count = 0;

    NODE *currentNode = root;

    while (currentNode->nextNode != NULL)
    {
        currentNode = currentNode->nextNode;
        count++;
    }

    return count;
}

int dequeue(NODE **root)
{
    NODE **removedNode = root;

    unsigned int wait = (**root).waitTime;

    NODE *newRoot = (**root).nextNode;

    *root = newRoot;

    free(*removedNode);
    
    return wait;
}

int incrementWaits(NODE *root)
{
}