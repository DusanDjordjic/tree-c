#ifndef _NODE_H_
#define _NODE_H_

#define INDENT_STEP 4
typedef struct Node Node;

struct Node {
    int level;
    unsigned int child_capacity;
    unsigned int child_count;
    Node* parent;
    Node** nodes; // This could be dynamic
    void* data;
};

int node_insert(Node* parent, Node* child);
Node* node_create(Node* parent, unsigned int child_count, void* data);
void node_print_tree(Node* node, void (*data_print)(const void*), int level, unsigned int indent);
void node_print(Node* node, void (*data_print)(const void*));
void node_free(Node* node, void (*data_free)(void*));
int node_set_data(Node* node, void* data);
int node_remove_data(Node* node, void (*data_free)(void*));

#endif
