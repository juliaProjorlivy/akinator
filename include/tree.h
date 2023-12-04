#ifndef BI_TREE
#define BI_TREE

struct tree_node
{
    char *value;
    struct tree_node *right;
    struct tree_node *left;
};

#endif
