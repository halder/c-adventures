#include <stdio.h>
#include "list.h"

int main(void)
{
    Node *n1, *n2, *n3, *n4, *n5;
    Node *pop1, *pop2;
    Node *by_index, *by_value;
    List *list;

    // `node_init` test
    n1 = node_init(10);
    n2 = node_init(20);
    n3 = node_init(30);
    n4 = node_init(40);
    n5 = node_init(50);
    printf("--- Initialized 5 nodes successfully:\n");
    printf("\tnode 1: %d, addr: %p\n", n1->data, (void *) n1);
    printf("\tnode 2: %d, addr: %p\n", n2->data, (void *) n2);
    printf("\tnode 3: %d, addr: %p\n", n3->data, (void *) n3);
    printf("\tnode 4: %d, addr: %p\n", n4->data, (void *) n4);
    printf("\tnode 5: %d, addr: %p\n", n5->data, (void *) n5);
    printf("\n");
    
    // `list_init` test
    list = list_init(n1);
    printf("--- Initialized list successfully:\n");
    printf("\thead: %p\n", (void *) list->head);
    printf("\ttail: %p\n", (void *) list->tail);
    printf("\tlength: %d\n", list->length);
    printf("\treversed: %d\n", list->reversed);
    printf("\n");

    // `list_push_back` test
    list_push_back(list, n2);
    list_push_back(list, n3);
    printf("--- Pushed two elements to list back successfully (updated tail):\n");
    printf("\thead: %p\n", (void *) list->head);
    printf("\ttail: %p\n", (void *) list->tail);
    printf("\tlength: %d\n", list->length);
    printf("\n");

    // `list_print` test
    printf("--- Printing current list, expected: '10, 20, 30'\n\t");
    list_print(list);
    printf("\n");

    // `list_push_front` test
    list_push_front(list, n4);
    list_push_front(list, n5);
    printf("--- Pushed two elements to list front successfully (updated head):\n");
    printf("\thead: %p\n", (void *) list->head);
    printf("\ttail: %p\n", (void *) list->tail);
    printf("\tlength: %d\n", list->length);
    printf("\n");

    printf("--- Printing current list, expected: '50, 40, 10, 20, 30'\n\t");
    list_print(list);
    printf("\n");

    // `list_pop_back` test
    printf("--- Popping back off list:\n");
    pop1 = list_pop_back(list);
    printf("--- Printing current list, expected: '50, 40, 10, 20'\n\t");
    list_print(list);
    printf("--- Popped element from list (expected 30): \n\t%d (is detached? - %d)\n", pop1->data, (pop1->prev == pop1->next));
    printf("\n");
    
    // `list_pop_front` test
    printf("--- Popping front off list:\n");
    pop2 = list_pop_front(list);
    printf("--- Printing current list, expected: '40, 10, 20'\n\t");
    list_print(list);
    printf("--- Popped element from list (expected 50): \n\t%d (is detached? - %d)\n", pop2->data, (pop2->prev == pop2->next));
    printf("\n");

    // `list_node_at_index` test
    by_index = list_node_at_index(list, 1);
    printf("--- Expected `list[1] == 10`, found:\n\t%d\n", by_index->data);
    printf("--- Trying to access index out of bounds (5):\n\t");
    by_index = list_node_at_index(list, 5);
    printf("\n");

    // `list_find_node_by_value` test
    by_value = list_find_node_by_value(list, 20);
    printf("--- Looking for '20', found: \n\t%d\n", by_value->data);
    printf("--- Looking for '50' (does not exist):\n\t");
    by_value = list_find_node_by_value(list, 50);
    printf("\n");

    printf("--- Fill list back up:\n\t");
    list_push_back(list, n3);
    list_push_back(list, n5);
    list_print(list);
    printf("\n");

    // `list_remove_value` test
    list_remove_value(list, 20);
    printf("--- Removed '20' from list, expected: '40, 10, 30, 50'\n\t");
    list_print(list);
    printf("--- Trying to remove '60' (does not exist):\n\t");
    list_remove_value(list, 60);

    printf("\n****** Reversed list tests ******\n\n");

    // `list_reverse` test
    printf("--- Original list:\n\t");
    list_print(list);
    printf("--- Reversed list, expected '50, 30, 10, 40':\n\t");
    list_reverse(list);
    list_print(list);

    printf("--- Popping off back of reversed list, expected: '50, 30, 10':\n\t");
    pop1 = list_pop_back(list);
    list_print(list);
    printf("--- Popping off front of reversed list, expected: '30, 10':\n\t");
    pop2 = list_pop_front(list);
    list_print(list);

    printf("--- Pushing former back to front of reversed list, expected: '40, 30, 10':\n\t");
    list_push_front(list, pop1);
    list_print(list);
    printf("--- Pushing former front to back of reversed list, expected: '40, 30, 10, 50':\n\t");
    list_push_back(list, pop2);
    list_print(list);

    by_index = list_node_at_index(list, 1);
    printf("--- Expected `list[1] == 30`, found: \n\t%d\n", by_index->data);
    by_index = list_node_at_index(list, 3);
    printf("--- Expected `list[3] == 50`, found: \n\t%d\n", by_index->data);

    printf("--- Reversing list back to original order, expected: '50, 10, 30, 40':\n\t");
    list_reverse(list);
    list_print(list);

    printf("\n***** Testing finished. Please check `stdout` to validate functionality. *****\n");

    return 0;
}
