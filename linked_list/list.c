#include <stdio.h>
#include <stdlib.h>

#include "list.h"

Node *node_init(int data)
{
    Node *node;

    if ((node = malloc(sizeof *node)) == NULL) {
        printf("Error allocating memory for new node of size %zu!\n", sizeof *node);
        return NULL;
    }

    node->data = data;
    node->prev = NULL;
    node->next = NULL;
    
    return node;
}

List *list_init(Node *genesis_node)
{
    List *new_list;

    if ((new_list = malloc(sizeof *new_list)) == NULL) {
        printf("Error allocating memory for new list of size %zu!\n", sizeof *new_list);
        return NULL;
    }
    
    new_list->length = 1;
    new_list->head = genesis_node;
    new_list->tail = genesis_node;
    new_list->reversed = 0;

    genesis_node->prev = NULL;
    genesis_node->next = NULL;
    
    return new_list;
}

void list_push_back(List *list, Node *node)
{
    if (!list->reversed) {
        node->prev = list->tail;
        node->next = NULL;
        
        list->tail->next = node;
        list->tail = node;
    } else {
        node->prev = NULL;
        node->next = list->head;

        list->head->prev = node;
        list->head = node;
    }
    list->length++;
}

void list_push_front(List *list, Node *node)
{
    if (!list->reversed) {
        node->prev = NULL;
        node->next = list->head;

        list->head->prev = node;
        list->head = node;
    } else {
        node->prev = list->tail;
        node->next = NULL;

        list->tail->next = node;
        list->tail = node;
    }
    list->length++;
}

Node *list_pop_back(List *list)
{
    Node *new_tail, *tail;

    if (!list->reversed) {
        tail = list->tail;
        new_tail = list->tail->prev;

        new_tail->next = NULL;
        list->tail = new_tail;
    } else {
        tail = list->head;
        new_tail = list->head->next;

        new_tail->prev = NULL;
        list->head = new_tail;
    }

    list->length--;
    tail->prev = NULL;
    tail->next = NULL;

    return tail;
}

Node *list_pop_front(List *list)
{
    Node *new_head, *head;

    if (!list->reversed) {
        head = list->head;
        new_head = list->head->next;

        new_head->prev = NULL;
        list->head = new_head;
    } else {
        head = list->tail;
        new_head = list->tail->prev;

        new_head->next = NULL;
        list->tail = new_head;
    }

    list->length--;
    head->prev = NULL;
    head->next = NULL;

    return head;
}

/*
 * Returns the Node at index `index`.
 * In case of duplicate entries, return the first encountered.
 */
Node *list_node_at_index(List *list, int index)
{   
    if (index >= list->length || index < 0) {
        printf("Provided index out of bounds!\n");
        return NULL;
    }

    Node *current, *found = NULL;
    int i = 0;

    if (!list->reversed) {
        current = list->head;
    } else {
        current = list->tail;
    }

    if (!index) {
        found = current;
    }

    while (i <= index) {
        if (i == index) {
            found = current;
        }
        if (!list->reversed) {
            current = current->next;
        } else {
            current = current->prev;
        }
        i++;
    }

    return found;
}

/*
 * Returns Node by value.
 * In case of duplicate entries, return the first encountered.
 */
Node *list_find_node_by_value(List *list, int data)
{
    Node *current, *found = NULL;
    
    if (!list->reversed) {
        current = list->head;
    } else {
        current = list->tail;
    }

    while (current) {
        if (current->data == data) {
            found = current;
        }
        if (!list->reversed) {
            current = current->next;
        } else {
            current = current->prev;
        }
    }

    if (!found) {
        printf("Value not found in list!\n");
    }

    return found;
}

/*
 * Removes Node by value. This also frees the memory allocated for the Node!
 * In case of duplicate entries, removes first Node encountered.
 */
void list_remove_value(List *list, int data)
{
    Node *current, *remove;

    if (!list->reversed) {
        current = list->head;
    } else {
        current = list->tail;
    }

    while (current) {
        if (current->data == data) {
            remove = current;
            current->prev->next = current->next;
            current->next->prev = current->prev;
            free(remove);
            return;
        }

        if (!list->reversed) {
            current = current->next;
        } else {
            current = current->prev;
        }
    }
    printf("No Node with value %d has been found!\n", data);
}

/*
 * Trick to "reverse" list in O(1) time (only works for doubly linked lists).
 */
void list_reverse(List *list)
{
    list->reversed = list->reversed ^ 1;
}

void list_print(List *list)
{
    Node *current;
    
    if (!list->reversed) {
        current = list->head;

        while (current->next) {
            printf("%d, ", current->data);
            current = current->next;
        }
        printf("%d\n", current->data);
    } else {
        current = list->tail;
    
        while (current->prev) {
            printf("%d, ", current->data);
            current = current->prev;
        }
        printf("%d\n", current->data);
    }
}

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
