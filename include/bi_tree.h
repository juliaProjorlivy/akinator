#ifndef BI_TREE
#define BI_TREE

#include "stack_func.h"

struct tree_node
{
    const char *value;
    struct tree_node *right;
    struct tree_node *left;
};

struct Tree
{
    struct tree_node *root;
    int size;
};

#endif
