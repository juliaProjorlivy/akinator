#include "bi_tree_func.h"
#include "bi_tree_ctor_dtor.h"
#include "verror.h"
#include <stdio.h>

struct tree_node *add_node(struct tree_node *node, elem_t val)
{
    struct tree_node *new_node = New(val);
    if(!new_node)
    {
        VERROR_MEM;
        return NULL;
    }

    else if(val <= node->value)
    {
        node->left = new_node;
    }
    else if(val > node->value)
    {
        node->right = new_node;
    }

    return new_node;
}

