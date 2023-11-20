#ifndef BI_TREE_DUMP
#define BI_TREE_DUMP

#include "bi_tree.h"

void print_pre_node(const tree_node *node);

void print_post_node(const tree_node *node);

void print_in_node(struct tree_node *node, char **line);

void node_dump(struct tree_node *node);

void tree_dump(struct tree_node *node);


#endif
