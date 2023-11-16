#include "bi_tree_ctor_dtor.h"
#include "verror.h"
#include <stdlib.h>

const int max_length = 50;

struct tree_node *New(const char *val)
{
    struct tree_node *node = (struct tree_node *)calloc(sizeof(tree_node), 1);
    if(!node)
    {
        VERROR_MEM;
        return NULL;
    }
    
    char *check_val = (char *)calloc(sizeof(char), max_length);
    if(!check_val)
    {
        VERROR_MEM;
        free(node);
        return NULL;
    }
    node->value = strncpy(check_val, val,  max_length);
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
    free(node->value);
    free(node);
}

