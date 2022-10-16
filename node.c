#include "node.h"
#include <stdio.h>
#include <stdlib.h>

Node* node_create(Node* parent, unsigned int child_capacity, void* data)
{
    Node* new_node = malloc(sizeof(Node));

    new_node->child_count = 0;
    new_node->child_capacity = child_capacity;
    new_node->data = data;
    new_node->parent = parent;

    new_node->nodes = malloc(sizeof(Node*) * child_capacity);

    if (parent == NULL)
        new_node->level = 1;
    else {
        if (node_insert(parent, new_node) != 0) {
            free(new_node->nodes);
            free(new_node);
            return NULL;
        }
        new_node->level = parent->level + 1;
    }

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

void node_print(Node* node, void (*data_print)(const void*))
{
    printf("%d", node->level);

    if (node->data != NULL && data_print != NULL)
        data_print(node->data);

    printf("\n");
}

void node_print_tree(Node* node, void (*data_print)(const void*), int level, unsigned int indent)
{

    for (unsigned int j = 0; j < indent; j++)
        printf(" ");
    node_print(node, data_print);

    if (level != 0) {
        for (unsigned int i = 0; i < node->child_count; i++) {
            node_print_tree(node->nodes[i], data_print, level - 1, indent + INDENT_STEP);
        }
    }
}

void node_free(Node* node, void (*data_free)(void*))
{
    Node* tmp = node;

    if (data_free != NULL && node->data != NULL)
        data_free(node->data);

    for (unsigned int i = 0; i < node->child_count; i++) {
        node_free(node->nodes[i], data_free);
    }

    free(tmp);
}

int node_set_data(Node* node, void* data)
{
    if (node->data != NULL)
        return -1;
    node->data = data;
    return 0;
}

int node_remove_data(Node* node, void (*data_free)(void*))
{
    if (node->data == NULL)
        return -1;
    data_free(node->data);
    node->data = NULL;
    return 0;
}
