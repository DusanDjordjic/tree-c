#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node* node_create(Node* parent, unsigned int child_capacity, void* data)
{
    Node* new_node = malloc(sizeof(Node));

    new_node->child_count = 0;
    new_node->child_capacity = child_capacity;
    new_node->data = data;
    new_node->parent = parent;

    if (parent == NULL)
        new_node->level = 1;
    else {
        if (node_insert(parent, new_node) != 0) {
            printf("Failed to insert node. No space left\n");
            free(new_node);
            return NULL;
        }
        new_node->level = parent->level + 1;
    }
    new_node->nodes = malloc(sizeof(Node*) * child_capacity);

    return new_node;
}

int node_insert(Node* parent, Node* child)
{
    if (parent->child_count == parent->child_capacity) {
        // No more space left to insert new node
        return -1;
    }
    parent->nodes[parent->child_count++] = child;
    return 0;
}

void node_print(Node* node, void (*n_print)(const Node*), void (*data_print)(const void*))
{
    n_print(node);

    if (node->data != NULL && data_print != NULL)
        data_print(node->data);

    printf("\n\n");
}

void node_print_tree(Node* node, void (*n_print)(const Node*), void (*data_print)(const void*), int level, unsigned int indent)
{
    if (node == NULL)
        return;

    for (unsigned int j = 0; j < indent; j++)
        printf(" ");
    node_print(node, n_print, data_print);

    if (level != 0) {
        for (unsigned int i = 0; i < node->child_count; i++) {
            node_print_tree(node->nodes[i], n_print, data_print, level - 1, indent + INDENT_STEP);
        }
    }
}

void node_free(Node* node, void (*data_free)(void*))
{
    if (node == NULL)
        return;

    if (data_free != NULL && node->data != NULL)
        data_free(node->data);

    for (unsigned int i = 0; i < node->child_count; i++) {
        node_free(node->nodes[i], data_free);
    }

    free(node);
}

int node_set_data(Node* node, void* data)
{
    if (node == NULL)
        return -1;

    if (node->data != NULL)
        return -2;

    node->data = data;

    return 0;
}

int node_remove_data(Node* node, void (*data_free)(void*))
{
    if (node == NULL)
        return -1;

    if (node->data == NULL)
        return -2;

    if (data_free == NULL)
        return -3;

    data_free(node->data);
    node->data = NULL;

    return 0;
}

int node_remove(Node* parent, unsigned int index, void (*data_free)(void*))
{
    if (index > parent->child_count - 1) {
        // That node doesn't exist
        return -1;
    }

    node_free(parent->nodes[index], data_free);

    parent->nodes[index] = NULL;
    // if this fails that means that we removed last node
    // and there is no need to push anything back
    // return 0;

    if (index != parent->child_count - 1) {
        unsigned long offset = sizeof(Node*) * parent->child_count - 1 - index;
        memmove(parent->nodes + index, parent->nodes + index + 1, offset);
    }

    parent->child_count--;

    return 0;
}
