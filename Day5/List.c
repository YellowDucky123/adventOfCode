#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "List.h"
struct node {
    int v1;
    int v2;
    struct node* next;
};

struct node* insertList(struct node* head, int v1, int v2) {
    struct node* new = malloc(sizeof(*new));
    new->v1 = v1;
    new->v2 = v2;
    new->next = NULL;

    if(head == NULL) {
        return new;
    }

    for(struct node* curr = head; 1; curr = curr->next) {
        if(curr->next == NULL) {
            curr->next = new;
            break;
        }
    }
    return head;
}