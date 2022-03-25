
struct node
{
    unsigned int waitTime;
    struct node *nextNode
};
typedef struct node NODE;

int enqueue(NODE *root);
int dequeue(NODE *root);