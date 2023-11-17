#include "bi_tree_func.h"
#include "bi_tree_ctor_dtor.h"
#include "verror.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct tree_node *add_node(struct tree_node *node, const char *val)
{
    struct tree_node *new_node = New(val);
    if(!new_node)
    {
        VERROR_MEM;
        return NULL;
    }

    else if(strcmp(val, node->value) <=0)
    {
        node->left = new_node;
    }
    else if(strcmp(val, node->value) > 0)
    {
        node->right = new_node;
    }

    return new_node;
}

