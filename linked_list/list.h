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
    int reversed;
} List;

Node *node_init(int data);
List *list_init(Node *genesis_node);
void list_push_back(List *list, Node *node);
void list_push_front(List *list, Node *node);
Node *list_pop_back(List *list);
Node *list_pop_front(List *list);
Node *list_node_at_index(List *list, int index);
Node *list_find_node_by_value(List *list, int data);
void list_remove_value(List *list, int data);
void list_reverse(List *list);
void list_print(List *list);
void list_free(List *list);

#endif // LIST_H
