#include <stdio.h>
#include <stdlib.h>

typedef struct _q{
    int data;
    struct _q *next;
}q;

void en(q **head, q **tail, int data)
{
    q *node = (q*)malloc(sizeof(q));
    node->data = data;
    
    if(*tail == NULL){
        *tail = *head = node;
    } else {
        (*tail)->next = node;
        *tail = node;
    }
    
    printf("enqueue %d\n", data);
}

int de(q **head, q **tail)
{
    if(*head == NULL){
        return -1;
    } else {
        q *tmp = *head;
        int val = tmp->data;
        *head = (*head)->next;
        free(tmp);
        return val;
    }
}

int main() 
{
    q *head = NULL, *tail = NULL;
    en(&head, &tail, 1);
    en(&head, &tail, 2);
    printf("dequeue %d\n", de(&head, &tail));
    en(&head, &tail, 3);
    printf("dequeue %d\n", de(&head, &tail));
    en(&head, &tail, 4);
    printf("dequeue %d\n", de(&head, &tail));
    printf("dequeue %d\n", de(&head, &tail));
    printf("dequeue %d\n", de(&head, &tail));
    return 0;
}
