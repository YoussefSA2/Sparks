#include "./include/CoordinatesQueue.h"

/*
* @brief Create a new queue of Coordinates.
* @return A pointer to the newly created queue.
*/
CoordinatesQueue* createQueue() {
    CoordinatesQueue* queue = (CoordinatesQueue*) malloc(sizeof(CoordinatesQueue));
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

/*
* @brief Check if a queue is empty.
* @param queue The queue to check.
* @return true if the queue is empty, false otherwise.
*/
int isEmpty(CoordinatesQueue* queue) {
    return queue->head == NULL;
}

/*
* @brief Add a Coordinate to the queue.
* @param queue The queue.
* @param coordinates The coordinates to add.
*/
void addToQueue(CoordinatesQueue* queue, Coordinates coordinates) {
    QueueNode* node = (QueueNode*) malloc(sizeof(QueueNode));
    node->coordinates = coordinates;
    node->next = NULL;

    if (queue->head == NULL) {
        queue->head = node;
        queue->tail = node;
    } else {
        queue->tail->next = node;
        queue->tail = node;
    }
}

/*
* @brief Remove a Coordinate from the queue.
* @param queue The queue.
* @return The coordinates removed from the queue.
*/
Coordinates removeFromQueue(CoordinatesQueue* queue) {
    if (isEmpty(queue)) {
        Coordinates coordinates;
        coordinates.x = -1;
        coordinates.y = -1;
        return coordinates;
    }

    QueueNode* node = queue->head;
    queue->head = queue->head->next;
    Coordinates coordinates = node->coordinates;
    free(node);
    return coordinates;
}

