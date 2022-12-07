#ifndef COORDINATESQUEUE_H
#define COORDINATESQUEUE_H

#include "./Constants.h"
#include "./Coordinates.h"

#include <stdlib.h>

typedef struct QueueNode {
    Coordinates coordinates;
    struct QueueNode* next;
} QueueNode;

typedef struct CoordinatesQueue {
    QueueNode* head;
    QueueNode* tail;
} CoordinatesQueue;

CoordinatesQueue* createQueue();
void addToQueue(CoordinatesQueue* queue, Coordinates coordinates);
Coordinates removeFromQueue(CoordinatesQueue* queue);
int isEmpty(CoordinatesQueue* queue);

#endif
