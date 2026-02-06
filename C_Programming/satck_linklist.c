#include <stdio.h>
#include <stdlib.h>

/* Node structure */
typedef struct _s {
    int data;
    struct Node *next;
}s;

/* Push operation */
void push(s **top, int value) {
    s *newNode = (struct Node *)malloc(sizeof(s));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    newNode->data = value;
    newNode->next = *top;
    *top = newNode;

    printf("%d pushed onto stack\n", value);
}

/* Pop operation */
void pop(s **top) {
    if (*top == NULL) {
        printf("Stack is empty\n");
        return;
    }

    s *temp = *top;
    printf("%d popped from stack\n", temp->data);

    *top = temp->next;
    free(temp);
}

/* Peek operation */
void peek(s *top) {
    if (top == NULL) {
        printf("Stack is empty\n");
        return;
    }

    printf("Top element: %d\n", top->data);
}

/* Display stack */
void display(s *top) {
    if (top == NULL) {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack elements: ");
    while (top != NULL) {
        printf("%d ", top->data);
        top = top->next;
    }
    printf("\n");
}

int main() {
    s *top = NULL;

    push(&top, 1);
    push(&top, 2);
    pop(&top);
    push(&top, 3);
    pop(&top);
    push(&top, 4);

    display(top);

    pop(&top);
    peek(top);
    pop(&top);
    display(top);

    return 0;
}
