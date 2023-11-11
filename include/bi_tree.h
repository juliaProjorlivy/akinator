#ifndef BI_TREE
#define BI_TREE

#include "stack_func.h"

struct tree_node
{
    elem_t value;
    struct tree_node *right;
    struct tree_node *left;
};

#endif
