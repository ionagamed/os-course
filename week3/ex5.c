#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
    struct node_t * next;
    struct node_t * prev;
    int data;
} node_t;

void print_list(node_t * head) {
    while (head->next) {
        head = head->next;
        printf("%d ", head->data);
    }
    printf("\n");
}

int insert_node(int idx, int val, node_t * head) {
    if (idx < 0) {
        return -1;
    }
    int current_idx = 0;
    while (head->next && current_idx < idx) {
        head = head->next;
        current_idx++;
    }
    if (current_idx < idx) {
        return -1;
    }

    node_t * prev_next = head->next;
    node_t * new_node = malloc(sizeof(node_t));
    new_node->data = val;
    new_node->next = prev_next;
    new_node->prev = head;
    head->next = new_node;
    return 0;
}

int delete_node(int idx, node_t * head) {
    if (idx < 0) { 
        return -1;
    }
    int current_idx = 0;
    while (head->next && current_idx < idx) {
        head = head->next;
        current_idx++;
    }
    if (current_idx < idx) {
        return -1;
    }

    node_t * node_to_remove = head->next;
    node_t * left = head;
    node_t * right = node_to_remove->next;
    left->next = right;
    right->prev = left;

    free(node_to_remove);
    return 0;
}

int main() {
    node_t * head = malloc(sizeof(node_t));
    head->next = NULL;
    head->data = 0;

    insert_node(0, 1, head);
    insert_node(1, 3, head);
    insert_node(2, 2, head);

    delete_node(1, head);

    print_list(head);
}