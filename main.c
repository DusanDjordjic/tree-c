#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void str_print(const void* p)
{
    printf(" %s", (char*)p);
}

void str_free(void* p)
{
    free(p);
}
void n_print(const Node* node)
{
    printf("Level: %d", node->level);
    printf(" Parent: ");
    if (node->parent == NULL) {
        printf("No parent");
    } else {
        printf("%d", node->parent->level);
    }

    printf(" Child count: %d", node->child_count);
}

int main()
{
    Node* main_node = node_create(NULL, 3, strdup("Dusan 1"));
    node_create(main_node, 2, strdup("DUSAN 2.1"));
    node_create(main_node, 1, NULL);
    node_create(main_node, 4, strdup("DUSAN 2.3"));
    node_create(main_node->nodes[0], 0, strdup("DUSAN 2.1.1"));
    node_create(main_node->nodes[0], 0, strdup("DUSAN 2.1.2"));
    node_create(main_node->nodes[1], 0, strdup("DUSAN 2.3.1"));
    node_create(main_node->nodes[2], 0, strdup("DUSAN 2.3.1"));
    node_create(main_node->nodes[2], 0, strdup("DUSAN 2.3.2"));
    node_create(main_node->nodes[2], 0, strdup("DUSAN 2.3.3"));
    node_create(main_node->nodes[2], 0, strdup("DUSAN 2.3.4"));

    if (node_set_data(main_node->nodes[1], strdup("DUSAN 2.2")) != 0) {
        printf("Failed to set node data\n");
        exit(1);
    }

    if (node_remove_data(main_node->nodes[2], str_free) != 0) {
        printf("Failed to remove node data\n");
        exit(2);
    }

    printf("\n*****BEFORE REMOVAL*****\n\n");
    node_print_tree(main_node, n_print, str_print, -1, 0);

    printf("\n*****AFTER  REMOVAL*****\n\n");

    node_remove(main_node, 2, str_free);
    node_remove(main_node->nodes[0], 0, str_free);

    node_print_tree(main_node, n_print, str_print, -1, 0);

    node_free(main_node, str_free);
}
