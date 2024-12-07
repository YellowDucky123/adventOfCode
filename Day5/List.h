#ifndef LIST_H
#define LIST_H

#include <stdbool.h> // Provides the constants 'true' and 'false'
#include <stdio.h>
#include <stdlib.h>

struct node {
    int v1;
    int v2;
    struct node* next;
};

//insert into the list, inserts at the tail
struct node* insertList(struct node* head, int v1, int v2);

#endif