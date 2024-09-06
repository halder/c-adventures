#include <stdio.h>
#include <stdlib.h>

#include "list.h"

List *list_init(int data)
{
    List *new_list;
    Node *genesis_node;

    new_list = malloc(sizeof *new_list);
    genesis_node = malloc(sizeof *genesis_node);

    genesis_node->data = data;
    genesis_node->prev = NULL;
    genesis_node->next = NULL;

    new_list->length = 1;
    new_list->head = genesis_node;
    new_list->tail = genesis_node;
    
    printf("Initializing new list, starting with %d.\n", data);

    return new_list;
}

void list_print(List *list)
{
    Node *current = list->head;

    // list is only one element:
    if ((current->prev == NULL) && (current->next == NULL)) {
        printf("%d \n", current->data);
        return;
    } else {
        while (current->next) {
            printf("%d, ", current->data);
            current = current->next;
        }
        printf("%d\n", current->data);
    }
}

void list_push_back(List *list, int data)
{
    Node *new_node;
    
    new_node = malloc(sizeof *new_node);

    new_node->data = data;
    new_node->prev = list->tail;
    new_node->next = list->tail->next;
    
    list->tail->next = new_node;
    list->tail = new_node;
    list->length++;
}

void list_push_front(List *list, int data)
{
    Node *new_node;

    new_node = malloc(sizeof *new_node);

    new_node->data = data;
    new_node->prev = list->head->prev;
    new_node->next = list->head;

    list->head->prev = new_node;
    list->head = new_node;
    list->length++;
}

int list_pop_back(List *list)
{
    Node *new_tail;
    int data = list->tail->data;

    new_tail = list->tail->prev;
    new_tail->next = list->tail->next;
    
    free(list->tail);
    
    list->tail = new_tail;
    list->length--;

    return data;
}

int list_pop_front(List *list)
{
    Node *new_head;
    int data = list->head->data;

    new_head = list->head->next;
    new_head->prev = list->head->prev;

    free(list->head);

    list->head = new_head;
    list->length--;

    return data;
}

/*
 * Returns the Node at index `index`.
 * In case of duplicate entries, return the first encountered.
 */
Node *list_at(List *list, int index)
{   
    Node *current = list->head;
    int i = 0;
    while (i < list->length) {
        if (i == index) {
            return current;
        }
        current = current->next;
        i++;
    }
    return NULL;
}

/*
 * Returns Node by value.
 * In case of duplicate entries, return the first encountered.
 */
Node *list_find(List *list, int data)
{
    Node *current = list->head;
    while (current) {
        if (current->data == data) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// TODO: implement
void list_remove(List *list, int data);
void list_remove_node(List *list, Node *node);

void list_free(List *list)
{
    Node *current = list->head;

    while (current != list->tail) {
        current = current->next;
        free(current->prev);
    }
    // free tail node
    free(current);
    free(list);
}
