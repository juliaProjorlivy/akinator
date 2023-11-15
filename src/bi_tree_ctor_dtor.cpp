#include "bi_tree_ctor_dtor.h"
#include "verror.h"
#include <stdlib.h>

struct tree_node *New(const char *val)
{
    struct tree_node *node = (struct tree_node *)calloc(sizeof(tree_node), 1);
    if(!node)
    {
        VERROR_MEM;
        return NULL;
    }
    
    node->value = val;
    node->right = NULL;
    node->left = NULL;

    return node;
}

void Del(struct tree_node *node)
{
    if(!node)
    {
        return;
    }
    if(node->left)
    {
        Del(node->left);
    }
    if(node->right)
    {
        Del(node->right);
    }
    free(node);
}

