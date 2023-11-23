#ifndef BI_TREE_CTOR_DTOR_H
#define BI_TREE_CTOR_DTOR_H

#include "bi_tree.h"

struct tree_node *Node(const char *val); // TODO: name should include type

void Del_tree(struct tree_node *node);

struct tree_node *add_node(struct tree_node *node, const char *val);

void visit(struct tree_node *node, void func(void *));

#endif
