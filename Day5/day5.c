#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "List.h"

struct node* fillTable(FILE *fp);
int middleNumberLine(FILE *fp, struct node* table);
void updateArrayFill(int *update, char* string);
bool updateValidation(struct node* table, int *updates, int size);
int isNumberBefore(struct node* table, int num1, int num2);

int main(int argc, char* argv[]) {
    FILE *fp = stdin;

    struct node* table = fillTable(fp);

    int value = middleNumberLine(fp, table);

    printf("sum is = %d\n", value);

    return 0;
}

struct node* fillTable(FILE *fp) {
    struct node* head = NULL;
    char str[50];
    
    while(fgets(str, 50, fp)) {
        int v1, v2;
        if(sscanf(str, "%d | %d", &v1, &v2) != 2) {
            break;
        }

        head = insertList(head, v1, v2);
    }
    return head;
}

int middleNumberLine(FILE *fp, struct node* table) {
    int count = 0;
    char str[200];
    while(fgets(str, 200, fp)) {
        int length = strlen(str);
        int *updates = malloc(length * sizeof(int));
        if(updateValidation(table, updates, length)) {
            count += updates[length/2];
        }
    }
    return count;
}

void updateArrayFill(int *update, char* string) {
    char* res = strtok(string, ",");
    int index = 0;

    while(res != NULL) {
        int upd = atoi(res);
        update[index] = upd;
        index++;

        res = strtok(NULL, ",");
    }
}

bool updateValidation(struct node* table, int *updates, int size) {
    for(int i = 0; i < size; i++) {
        for(int j = i + 1; j < size; j++) {
            if(isNumberBefore(table, updates[i], updates[j]) == 0) {
                return false;
            }
            else if(isNumberBefore(table, updates[i], updates[j]) == 2 &&
                    isNumberBefore(table, updates[j], updates[i]) == 0) {
                return false;
            }
        }
    }

    return true;
}

// 2 means that there is nothing about the relationship of these 2 nums
// 1 is true
// 0 is false
int isNumberBefore(struct node* table, int num1, int num2) {
    for(struct node* curr = table; curr != NULL; curr = curr->next) {
        if(curr->v1 == num1 && curr->v2 == num2) {
            return 1;
        }
        if(curr->v1 == num2 && curr->v2 == num1) {
            return 0;
        }
    }

    return 2;
}
