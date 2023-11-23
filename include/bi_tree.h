#ifndef BI_TREE
#define BI_TREE

#include "stack_func.h"

struct tree_node
{
    char *value;
    struct tree_node *right;
    struct tree_node *left;
};

#endif
