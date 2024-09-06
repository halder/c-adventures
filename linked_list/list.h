#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct List {
    int length;
    struct Node *head;
    struct Node *tail;
} List;

List *list_init(int data);
void list_print(List *list);
void list_push_back(List *list, int data);
void list_push_front(List *list, int data);
int list_pop_back(List *list);
int list_pop_front(List *list);
Node *list_at(List *list, int index);
Node *list_find(List *list, int data);
void list_remove(List *list, int data);
void list_remove_node(List *list, Node *node);
void list_free(List *list);

#endif // LIST_H
