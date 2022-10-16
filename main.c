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

int main()
{
    Node* main_node = node_create(NULL, 3, strdup("Dusan 1"));
    node_create(main_node, 2, strdup("DUSAN 2.1"));
    node_create(main_node, 0, NULL);
    node_create(main_node, 0, strdup("DUSAN 2.3"));
    node_create(main_node->nodes[0], 0, strdup("DUSAN 2.1.1"));
    node_create(main_node->nodes[0], 0, strdup("DUSAN 2.1.2"));

    node_set_data(main_node->nodes[1], strdup("DUSAN 2.2"));
    node_remove_data(main_node->nodes[2], str_free);

    node_print_tree(main_node, str_print, -1, 0);

    node_free(main_node, NULL);
}
