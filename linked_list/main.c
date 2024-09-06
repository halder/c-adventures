/* Simple doubly linked list implementation. */

#include <stdio.h>
#include "list.h"

// TODO:
//  * turn this into test.c
//  * use <assert.h>
//  * init nodes outside of list functions?

int main(void)
{
    printf("Hello from main.c!\n\n");

    List *list;
    printf("--- init ---\n");
    if (!(list = list_init(1))) {
        return 1;
    }

    printf("--- Expected: 1\n");
    list_print(list);

    printf("--- append ---\n");
    list_push_back(list, 2);
    list_push_back(list, 3);
    list_push_back(list, 10);
    printf("--- Expected: 1, 2, 3, 10\n");
    list_print(list);
    printf("list length: %d.\n", list->length);
    
    printf("--- push front (insert) ---\n");
    list_push_front(list, 99);
    printf("--- Expected: 99, 1, 2, 3, 10\n");
    list_print(list);
    printf("list length: %d.\n", list->length);

    printf("--- find node by value ---\n");
    printf("--- Expected: 3 -> 3\n");
    Node *node_val_3 = list_find(list, 3);
    printf("Node found by value `3`: %d\n", node_val_3->data);

    printf("--- pop ---\n");
    int a = list_pop_back(list);
    list_pop_back(list);
    printf("--- Expected: 99, 1, 2\n");
    list_print(list);
    printf("list length: %d.\n", list->length);
    printf("popped from list, a: %d; (popped 3 not assigned)\n", a);

    printf("--- push back (append) ---\n");
    list_push_back(list, 70);
    printf("--- Expected: 99, 1, 2, 70\n");
    list_print(list);

    printf("--- pop front ---\n");
    int b = list_pop_front(list);
    printf("--- Expected: 1, 2, 70\n");
    list_print(list);
    printf("former head: %d.\n", b);

    printf("head of list: %d \ntail of list: %d\n", list->head->data, list->tail->data);

    printf("--- find node at `index` ---\n");
    printf("--- Expected: list[1] = 2\n");
    Node *node_at_index_1 = list_at(list, 1);
    printf("Node at index 1: %d\n", node_at_index_1->data);

    printf("--- free ---\n");
    list_free(list);

    // this segfaults -> working as intended?
    //list_print(list);

    printf("\nBye from main.c!\n");
    return 0;
}
