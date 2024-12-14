#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdbool.h>

typedef struct Book {
    int id;
    char title[100];
    char author[100];
    bool available;
} Book;

typedef struct User {
    int id;
    char name[100];
    int requestedBookId;
} User;

typedef struct StackNode {
    Book book;
    struct StackNode* next;
} StackNode;

typedef struct QueueNode {
    User user;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* head;
    QueueNode* tail;
} Queue;


void push(StackNode** top, Book book);
Book pop(StackNode** top);
void displayStack(StackNode* top);


Queue* initQueue();
void enqueue(Queue* queue, User user);
User dequeue(Queue* queue);
void displayQueue(Queue* queue);

#endif
