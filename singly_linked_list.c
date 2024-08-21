/* Singly linked list implementation.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int         data;
    struct Node *next;
} Node;

/* Returns a pointer to `head`. */
Node *linked_list_init(int data) {
    Node *head = malloc(sizeof(Node));

    // initial element == last element
    head->data = data;
    head->next = NULL;
    printf("Initializing linked list, starting with %d.\n", head->data);

    return head;
}

/* Insert an element to the front of the linked list,
 * effectively updating the `head` to the new element.
 *
 * Understanding: Since we want to update the pointer `head`,
 * which lives outside this function, we have to use a pointer to a pointer.
 */
void linked_list_insert(Node **head, int data)
{
    Node *new_node = malloc(sizeof(Node));

    new_node->data = data;
    new_node->next = *head; // "new" head points to "old" head

    *head = new_node; // update `head`
    printf("Inserting %d as new head of linked list.\n", new_node->data);
}

/* Append an element to the end of the linked list (by traversal).
 * Note: In order to do this in constant time, we would need a `tail` pointer.
 */ 
void linked_list_append(Node *head, int data)
{
    Node *current = head;
    Node *new_node = malloc(sizeof(Node));

    while (current->next != NULL) {
        current = current->next;
    }

    // current is now tail
    current->next = new_node;
    
    new_node->data = data;
    new_node->next = NULL;
    printf("Appending %d to linked list.\n", new_node->data);
}

/* Traverse linked list and print contents. */
void linked_list_print(Node *head)
{
    Node *temp = head;

    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\n");
}

/* Free entire linked list by traversal.
 * Look ahead of `head` using a helper variable, then free
 * `head` iteratively.
 * Helper variable to avoid segfault? Not 100% sure.
 */
void linked_list_free(Node *head)
{
    Node *temp = head;

    if (temp->next == NULL) {
        printf("Removing one-element (%d) linked list.\n", temp->data);
        free(head);
    } else {
        temp = temp->next;
    }

    printf("Freeing linked list starting at: ");

    while (temp != NULL) {
        printf("%d, ", head->data);
        free(head);
        head++;
        temp = temp->next;
    }
    printf("%d\n", head->data);
    free(head);
}

/* Remove last item of linked list by traversal.
 * Note: In order to do this in constant time, we would need a `tail` pointer.
 */
void linked_list_remove_tail(Node *head)
{
    Node *temp = head, *prev = head;

    if (temp->next == NULL) {
        linked_list_free(head);
        printf("call linked_list_free(&head).\n");
        return;
    } else {
        temp = temp->next;
    }

    while (temp->next != NULL) {
        temp = temp->next;
        prev = prev->next;
    }
    
    // new tail
    prev->next = NULL;

    printf("Removing %d from linked list.\n", temp->data);
    free(temp);
}

/* Remove head of linked list.
 * Updates former head.next to be new `head`.
 * 
 * Understanding: Since we want to delete and update the head, 
 * we have to use a pointer to a pointer.
 */
void linked_list_remove_head(Node **head)
{
    Node *previous_head = *head;
    *head = (*head)->next;

    printf("Removing previous head %d from linked list.\n", previous_head->data);
    free(previous_head);
}

/* Tests. */
int main(void)
{
    Node *head;
    printf("--- init ---\n");
    head = linked_list_init(1);

    printf("--- append ---\n");
    linked_list_append(head, 2);
    linked_list_append(head, 3);
    linked_list_append(head, 10);
    printf("--- Expected: 1, 2, 3, 10\n");
    linked_list_print(head);

    printf("--- insert ---\n");
    linked_list_insert(&head, 99);
    printf("--- Expected: 99, 1, 2, 3, 10\n");
    linked_list_print(head);

    printf("--- remove tail ---\n");
    linked_list_remove_tail(head);
    linked_list_remove_tail(head);
    printf("--- Expected: 99, 1, 2\n");
    linked_list_print(head);

    printf("--- append ---\n");
    linked_list_append(head, 70);
    printf("--- Expected: 99, 1, 2, 70\n");
    linked_list_print(head);

    printf("--- remove head ---\n");
    linked_list_remove_head(&head);
    printf("--- Expected: 1, 2, 70\n");
    linked_list_print(head);

    printf("--- free ---\n");
    linked_list_free(head);

    // this segfaults -> working as intended?
    //linked_list_print(head);

    return 0;
}
