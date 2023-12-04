#include "ctor_dtor.h"
#include "verror.h"
#include <stdlib.h>

const int max_length = 100;

struct tree_node *Node(const char *val)
{
    struct tree_node *node = (struct tree_node *)calloc(sizeof(tree_node), 1);
    if(!node)
    {
        VERROR_MEM;
        return NULL;
    }

    node->right = NULL;
    node->left = NULL;
    
    if(val == NULL)
    {
        node->value = NULL;
        return node;
    }

    char *check_val = strndup(val, max_length);
    if(!check_val)
    {
        VERROR_MEM;
        free(node);
        return NULL;
    }

    node->value = check_val;
    return node;

    // TODO: strdup instead of cpy. Also check that it's not null. If it's null -> value = null
}



void Del_tree(struct tree_node *node)
{
    if(!node)
    {
        return;
    }
    if(node->left)
    {
        Del_tree(node->left);
    }
    if(node->right)
    {
        Del_tree(node->right);
    }
    free(node->value);
    free(node);
}

struct tree_node *add_node(struct tree_node *node, const char *val)
{
    struct tree_node *new_node = Node(val);
    if(!new_node)
    {
        VERROR_MEM;
        return NULL;
    }
    
    if(strcmp(val, node->value) <= 0)
    {
        node->left = new_node;
    }
    else
    {
        node->right = new_node;
    }

    return new_node;
}
