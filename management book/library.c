 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

void addBook(Book** inventory, int* bookCount) {
    Book newBook;
    printf("Enter Book ID: ");
    scanf("%d", &newBook.id);
    printf("Enter Book Title: ");
    getchar();
    fgets(newBook.title, sizeof(newBook.title), stdin);
    strtok(newBook.title, "\n");
    printf("Enter Author Name: ");
    fgets(newBook.author, sizeof(newBook.author), stdin);
    strtok(newBook.author, "\n");
    newBook.available = true;

    (*inventory)[*bookCount] = newBook;
    (*bookCount)++;
    printf("Book added successfully!\n");
}

void searchBook(Book* inventory, int bookCount) {
    char searchQuery[100];
    printf("Enter Book Title or ID to Search: ");
    getchar();
    fgets(searchQuery, sizeof(searchQuery), stdin);
    strtok(searchQuery, "\n");

    int found = 0;

    for (int i = 0; i < bookCount; i++) {

        if (strstr(inventory[i].title, searchQuery) != NULL ||
            atoi(searchQuery) == inventory[i].id) {
            printf("Book Found:\n");
            printf("ID: %d, Title: %s, Author: %s, Available: %s\n",
                   inventory[i].id, inventory[i].title, inventory[i].author,
                   inventory[i].available ? "Yes" : "No");
            found = 1;
        }
    }

    if (!found) {
        printf("No matching book found.\n");
    }
}

void processRequests(StackNode** stack, Book* inventory, int bookCount, Queue* borrowQueue) {
    if (borrowQueue->head == NULL) {
        printf("No requests in the queue to process.\n");
        return;
    }

    User user = dequeue(borrowQueue);
    for (int i = 0; i < bookCount; i++) {
        if (inventory[i].id == user.requestedBookId && inventory[i].available) {
            inventory[i].available = false;
            printf("Request processed for User ID: %d, Name: %s, Book: %s\n",
                   user.id, user.name, inventory[i].title);
            return;
        }
    }
    printf("Book for User ID %d is still unavailable.\n", user.id);
}

void returnBook(StackNode** stack, Book* inventory, int bookCount) {
    int bookId;
    printf("Enter Book ID to Return: ");
    scanf("%d", &bookId);

    for (int i = 0; i < bookCount; i++) {
        if (inventory[i].id == bookId) {
            inventory[i].available = true;
            push(stack, inventory[i]);
            printf("Book returned successfully and added to the recently returned stack.\n");
            return;
        }
    }
    printf("Book not found.\n");
}


void borrowBook(Book* inventory, int bookCount, Queue* borrowQueue) {
    int bookId;
    printf("Enter Book ID to Borrow: ");
    scanf("%d", &bookId);

    for (int i = 0; i < bookCount; i++) {
        if (inventory[i].id == bookId) {
            if (inventory[i].available) {
                inventory[i].available = false;
                printf("You have successfully borrowed the book: %s\n", inventory[i].title);
            } else {
                User newUser;
                printf("Book is currently unavailable. Enter your User ID: ");
                scanf("%d", &newUser.id);
                printf("Enter your Name: ");
                getchar();
                fgets(newUser.name, sizeof(newUser.name), stdin);
                strtok(newUser.name, "\n");
                newUser.requestedBookId = bookId;
                enqueue(borrowQueue, newUser);
                printf("You have been added to the borrow request queue.\n");
            }
            return;
        }
    }
    printf("Book not found.\n");
}




int main() {
    Book* inventory = (Book*)malloc(100 * sizeof(Book));
    int bookCount = 0;

    StackNode* recentlyReturned = NULL;
    Queue* borrowQueue = initQueue();

    int choice;

    printf("===== Library Book Management System =====\n");

    do {
        printf("\nMenu:\n");
        printf("1. Add New Book\n");
        printf("2. Borrow Book\n");
        printf("3. Return Book\n");
        printf("4. Process Borrow Requests\n");
        printf("5. View Recently Returned Books\n");
        printf("6. Display Borrow Request Queue\n");
        printf("7. Search for a Book\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook(&inventory, &bookCount);
                break;
            case 2:
                borrowBook(inventory, bookCount, borrowQueue);
                break;
           case 3: {
    int bookId;
    printf("Enter Book ID to Return: ");
    scanf("%d", &bookId);

    bool found = false;

    for (int i = 0; i < bookCount; i++) {
        if (inventory[i].id == bookId) {
            found = true;
            if (inventory[i].available) {
                printf("This book has not been borrowed. You cannot return it.\n");
            } else {
                inventory[i].available = true;
                push(&recentlyReturned, inventory[i]);
                printf("Book returned successfully.\n");
            }
            break;
        }
    }

    if (!found) {
        printf("Book ID not found in the inventory.\n");
    }
    break;
}

                break;
            case 4:
                processRequests(&recentlyReturned, inventory, bookCount, borrowQueue);
                break;
            case 5:
                displayStack(recentlyReturned);
                break;
            case 6:
                displayQueue(borrowQueue);
                break;
            case 7:
                searchBook(inventory, bookCount);
                break;
            case 8:
                printf("Exiting the system. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 8);

    free(inventory);
    while (recentlyReturned != NULL) pop(&recentlyReturned);
    while (borrowQueue->head != NULL) dequeue(borrowQueue);
    free(borrowQueue);

    return 0;
}
