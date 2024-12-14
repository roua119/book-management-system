 #include <stdio.h>
#include <stdlib.h>
#include "library.h"

void push(StackNode** top, Book book) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode) {
        printf("Memory allocation failed for stack node.\n");
        return;
    }
    newNode->book = book;
    newNode->next = *top;
    *top = newNode;
}

Book pop(StackNode** top) {
    if (*top == NULL) {
        printf("Stack is empty.\n");
        Book emptyBook = {0, "", "", false};
        return emptyBook;
    }
    StackNode* temp = *top;
    Book book = temp->book;
    *top = temp->next;
    free(temp);
    return book;
}

void displayStack(StackNode* top) {
    if (top == NULL) {
        printf("No books in the recently returned stack.\n");
        return;
    }
    printf("Recently Returned Books:\n");
    StackNode* current = top;
    while (current != NULL) {
        printf("ID: %d, Title: %s, Author: %s\n", current->book.id, current->book.title, current->book.author);
        current = current->next;
    }
}
