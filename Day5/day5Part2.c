#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct node* fillTable(FILE *fp);
int middleNumberLine(FILE *fp, struct node* table);
int updateArrayFill(int *update, char* string);
bool updateValidation(struct node* table, int *updates, int size);
int isNumberBefore(struct node* table, int num1, int num2);
struct node* insertList(struct node* head, int v1, int v2);
void freeList(struct node* head);
void moveData(int *update, int size, int index1, int moveTo);
void updateFix(int *update, int size, struct node* table);

struct node {
    int v1;
    int v2;
    struct node* next;
};

int main(int argc, char* argv[]) {
    FILE *fp = stdin;

    struct node* table = fillTable(fp);

    int value = middleNumberLine(fp, table);

    printf("\nsum is = %d\n\n", value);

    freeList(table);

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
        int size = updateArrayFill(updates, str);

        if(!updateValidation(table, updates, length)) {
            updateFix(updates, size, table);
            count += updates[size/2];
        }

        free(updates);
    }

    return count;
}

void updateFix(int *update, int size, struct node* table) {
    for(int i = 0; i < size; i++) {
        int j = i + 1;
        while(j < size) {
            if(isNumberBefore(table, update[j], update[i])) {
                moveData(update, size, j, i);
            }
            else {
                j++;
            }
        }
    }
}

void moveData(int *update, int size, int index1, int moveTo) {
    int tmp = update[index1];
    for(int i = index1; i > moveTo; i--) {
        update[i] = update[i - 1];
    }
    update[moveTo] = tmp;
}

int updateArrayFill(int *update, char* string) {
    char* res = strtok(string, ",");
    int index = 0;

    while(res != NULL) {
        int upd = atoi(res);

        update[index] = upd;
        index++;

        res = strtok(NULL, ",");
    }
    return index;
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

void freeList(struct node* head) {
    struct node* curr = head;
    while(curr != NULL) {
        struct node* tmp = curr->next;
        free(curr);
        curr = tmp;
    }
}