#ifndef BI_TREE_CTOR_DTOR_H
#define BI_TREE_CTOR_DTOR_H

#include "tree.h"

struct tree_node *Node(const char *val);

void Del_tree(struct tree_node *node);

struct tree_node *add_node(struct tree_node *node, const char *val);

#endif
