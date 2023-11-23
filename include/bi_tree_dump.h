#ifndef BI_TREE_DUMP
#define BI_TREE_DUMP

#include "bi_tree.h"

void print_in_node(struct tree_node *node, char **line);

void node_dump(struct tree_node *node, FILE *file);

int tree_dump(struct tree_node *node, const char *filename);


#endif
