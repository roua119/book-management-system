
#include <stdio.h>
#include <stdlib.h>
#include "library.h"

Queue* initQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (!queue) {
        printf("Memory allocation failed for queue.\n");
        return NULL;
    }
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

void enqueue(Queue* queue, User user) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (!newNode) {
        printf("Memory allocation failed for queue node.\n");
        return;
    }
    newNode->user = user;
    newNode->next = NULL;

    if (queue->tail == NULL) {
        queue->head = queue->tail = newNode;
        return;
    }

    queue->tail->next = newNode;
    queue->tail = newNode;
}

User dequeue(Queue* queue) {
    if (queue->head == NULL) {
        printf("Borrow request queue is empty.\n");
        User emptyUser = {0, "", 0};
        return emptyUser;
    }

    QueueNode* temp = queue->head;
    User user = temp->user;
    queue->head = temp->next;

    if (queue->head == NULL)
        queue->tail = NULL;

    free(temp);
    return user;
}

void displayQueue(Queue* queue) {
    if (queue->head == NULL) {
        printf("No users in the borrow request queue.\n");
        return;
    }
    printf("Borrow Request Queue:\n");
    QueueNode* current = queue->head;
    while (current != NULL) {
        printf("User ID: %d, Name: %s, Requested Book ID: %d\n",
               current->user.id, current->user.name, current->user.requestedBookId);
        current = current->next;
    }
}
