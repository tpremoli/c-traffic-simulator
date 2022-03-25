#include <queue.h>

int enqueue(NODE **root)
{
    NODE *newNode;
    if ((newNode = (NODE *)malloc(sizeof(NODE))) == NULL)
    {
        printf("Out of memory!\n");
        exit(1);
    }
    else
    {
        if ((**root).nextNode == NULL)
        {
            printf("Enqueuing first node\n");
            
            newNode->waitTime = 0;
            newNode->nextNode = NULL;

            (**root).nextNode = newNode;
        }
        else
        {
            NODE *currentNode = (**root).nextNode;

            while (currentNode->nextNode != NULL)
            {
                currentNode = currentNode->nextNode;
            }

            newNode->waitTime = 0;
            newNode->nextNode = NULL;

            currentNode->nextNode = newNode;
        }
    }

    return 0;
}

int countNodes(NODE *root)
{

    if (root->nextNode  == NULL)
    {
        printf("root is null\n");
        return 0;
    }

    unsigned int count = 1;

    NODE *currentNode = root->nextNode;

    while (currentNode->nextNode != NULL)
    {
        currentNode = currentNode->nextNode;
        count++;
    }

    return count;
}

int dequeue(NODE **root)
{
    if ((**root).nextNode  == NULL)
    {
        return 0;
    }

    NODE **removedNode = (**root).nextNode;

    unsigned int wait = (**root).waitTime;

    NODE *newRoot = (**root).nextNode;

    *root = newRoot;

    free(*removedNode);

    return wait;
}

int incrementWaits(NODE *root)
{
    if (root->nextNode  == NULL)
    {
        return 0;
    }

    NODE *currentNode = root->nextNode;
    currentNode->waitTime = currentNode->waitTime + 1;

    while (currentNode->nextNode != NULL)
    {
        currentNode = currentNode->nextNode;
        currentNode->waitTime = currentNode->waitTime + 1;
    }

    return 0;
}

int printWaits(NODE *root)
{
    NODE *currentNode = root->nextNode;

    unsigned int count = 0;

    while (currentNode->nextNode != NULL)
    {
        printf("Node %d waited %d\n", count, currentNode->waitTime);
        currentNode = currentNode->nextNode;
        count++;
    }

    return 0;
}