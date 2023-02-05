
#include <stdio.h>
#include <stdlib.h>

/*Queue Structure Definition*/
struct queueStruct
{
    unsigned short int arrivalPeriod;
    struct queueStruct *nextNode;
};

typedef struct queueStruct QUEUE;

/*Queue Function Prototypes*/
QUEUE *newNode(unsigned short int);
void Push(unsigned short int, QUEUE*);
void Pop(QUEUE**);
void printQueue(QUEUE*);
