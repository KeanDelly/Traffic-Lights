
#include <util_queue.h>


QUEUE *newNode(unsigned short int x)
{
    QUEUE *node;
    if(!(node = (QUEUE*)malloc(sizeof(QUEUE))))
    {
        fprintf(stderr,"Not Enough Memory to Allocate New Node\n");
        exit(1);
    }
    node -> arrivalPeriod = x;
    node -> nextNode = NULL;
    return node;
}


void Push(unsigned short int x, QUEUE *root)
{
    if(!(root->nextNode == NULL))
        Push(x, root -> nextNode);
    else
    {
        QUEUE *node = newNode(x);
        root -> nextNode = node;
    }
}

void Pop(QUEUE **root)
{
    QUEUE *tempRoot = *root;
    *root = (*root) -> nextNode;
    free(tempRoot);
}


void printQueue(QUEUE *root)
{
    if(!(root == NULL)){
        printf("%d \n", root->arrivalPeriod);
        if(!(root->nextNode == NULL))
            printQueue(root->nextNode);
    }
    else
        printf("Queue is Empty\n");
}
