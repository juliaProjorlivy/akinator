#include "bi_tree_dump.h"
#include "verror.h"
#include <stdio.h>

void print_pre_node(const tree_node *node)
{
    if(!node)
    {
        printf("nil");
        return;
    }
    printf("(");
    printf(ELEM_PRINT_SPEC, node->value);
    print_pre_node(node->left);
    print_pre_node(node->right);
    printf(")");
}

void print_post_node(const tree_node *node)
{
    if(!node)
    {
        printf("nil");
        return;
    }
    printf("(");
    print_pre_node(node->left);
    print_pre_node(node->right);
    printf(ELEM_PRINT_SPEC, node->value);
    printf(")");
}

void print_in_node(const tree_node *node)
{
    if(!node)
    {
        printf("nil");
        return;
    }
    printf("(");
    print_pre_node(node->left);
    printf(ELEM_PRINT_SPEC, node->value);
    print_pre_node(node->right);
    printf(")");
}

void node_dump(struct tree_node *node)
{
    if(!node)
    {
        return;
    }
    printf("\tnode_%p[shape=record, label=\"val:" ELEM_PRINT_SPEC "\\n | { <f0> left | <f1> right}\", color=\"blue\"]", node, node->value);
    if(node->left)
    {
        printf("\tnode_%p:<f0>->node_%p;\n", node, node->left);
    }
    if(!node->right)
    {
        printf("\tnode_%p:<f1>->node_%p;\n", node, node->right);
    }
    node_dump(node->left);
    node_dump(node->right);
    
}

void tree_dump(struct tree_node *node)
{
    freopen("tree_graph.dot", "w", stdout);

    printf("digraph tree{\n");
    printf("\trankdir=TB;\n");
    node_dump(node);
    printf("};\n");
    
}
