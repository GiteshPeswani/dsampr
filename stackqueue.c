#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define URL_LENGTH 100

// Structure for Stack
typedef struct {
    char data[MAX][URL_LENGTH];
    int top;
} Stack;

// Structure for Queue
typedef struct {
    char data[MAX][URL_LENGTH];
    int front, rear, size;
} Queue;

// Function to initialize the stack
void initStack(Stack *stack) {
    stack->top = -1;
}

// Function to push URL onto the stack
void push(Stack *stack, const char *url) {
    if (stack->top < MAX - 1) {
        stack->top++;
        strcpy(stack->data[stack->top], url);
    } else {
        printf("Stack overflow\n");
    }
}

// Function to pop URL from the stack
char *pop(Stack *stack) {
    if (stack->top >= 0) {
        return stack->data[stack->top--];
    } else {
        printf("Stack underflow\n");
        return NULL;
    }
}

// Function to check if stack is empty
int isEmptyStack(Stack *stack) {
    return stack->top == -1;
}

// Function to initialize the queue
void initQueue(Queue *queue) {
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
}

// Function to enqueue URL into the queue
void enqueue(Queue *queue, const char *url) {
    if (queue->size < MAX) {
        queue->rear = (queue->rear + 1) % MAX;
        strcpy(queue->data[queue->rear], url);
        queue->size++;
    } else {
        printf("Queue overflow\n");
    }
}

// Function to display the browsing history
void displayQueue(Queue *queue) {
    if (queue->size == 0) {
        printf("No browsing history.\n");
        return;
    }
    printf("Browsing history:\n");
    for (int i = 0; i < queue->size; i++) {
        int index = (queue->front + i) % MAX;
        printf("%s\n", queue->data[index]);
    }
}

// Browser history management
void visit(Stack *backStack, Stack *forwardStack, Queue *historyQueue, const char *url) {
    push(backStack, url);
    enqueue(historyQueue, url);
    // Clear the forward stack when a new URL is visited
    initStack(forwardStack);
    printf("Visited: %s\n", url);
}

void back(Stack *backStack, Stack *forwardStack) {
    if (backStack->top > 0) {
        char *current = pop(backStack);
        push(forwardStack, current);
        printf("Moved back to: %s\n", backStack->data[backStack->top]);
    } else {
        printf("No pages to go back to.\n");
    }
}

void forward(Stack *backStack, Stack *forwardStack) {
    if (!isEmptyStack(forwardStack)) {
        char *current = pop(forwardStack);
        push(backStack, current);
        printf("Moved forward to: %s\n", current);
    } else {
        printf("No pages to go forward to.\n");
    }
}

int main() {
    Stack backStack, forwardStack;
    Queue historyQueue;

    initStack(&backStack);
    initStack(&forwardStack);
    initQueue(&historyQueue);

    int choice;
    char url[URL_LENGTH];

    while (1) {
        printf("\nBrowser History Menu:\n");
        printf("1. Visit a new URL\n");
        printf("2. Go back\n");
        printf("3. Go forward\n");
        printf("4. Display browsing history\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the URL to visit: ");
                scanf("%s", url);
                visit(&backStack, &forwardStack, &historyQueue, url);
                break;
            case 2:
                back(&backStack, &forwardStack);
                break;
            case 3:
                forward(&backStack, &forwardStack);
                break;
            case 4:
                displayQueue(&historyQueue);
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
