#include "bi_tree_dump.h"
#include "verror.h"
#include <stdio.h>

void print_pre_node(const tree_node *node)
{
    if(!node)
    {
        printf("nil ");
        return;
    }
    printf("( ");
    printf("\" %s \" ", node->value);
    print_pre_node(node->left);
    print_pre_node(node->right);
    printf(") ");
}

void print_post_node(const tree_node *node)
{
    if(!node)
    {
        printf("nil ");
        return;
    }
    printf("( ");
    print_post_node(node->left);
    print_post_node(node->right);
    printf("\" %s \" ", node->value);
    printf(") ");
}

void print_in_node(struct tree_node *node, char **line)
{
    int word_len = 0;
    if(!node)
    {
        sprintf(*line, "nil %n", &word_len);
        (*line) += word_len;
        return;
    }
    sprintf(*line, "( %n", &word_len);
    (*line) += word_len;
    print_in_node(node->left, line);
    sprintf(*line, "\" %s \" %n", node->value, &word_len);
    (*line) += word_len;
    print_in_node(node->right, line);
    sprintf(*line, ") %n", &word_len);
    (*line) += word_len;
}

void print_in_file(const char *filename, const char *line)
{
    FILE *file = fopen(filename, "w");
    fprintf(file, "%s", line);
    fclose(file);
}

void node_dump(struct tree_node *node)
{
    if(!node)
    {
        return;
    }
    printf("    node[color=\"blue\", frontsize=14, shape=\"rectangle\", style=\"rounded, filled\", fillcolor=\"lightblue\"];\n");
        printf("    edge[color=\"deepskyblue\",fontsize=12];\n");
    printf("\tnode_%p[shape=record, label=\"{%s\\n |  {<f0> left | <f1> right}}\", color=\"blue\", style=\"filled\", fillcolor=\"lightgreen\"];\n", node, node->value);
    if(node->left)
    {
        printf("\tnode_%p:<f0>->node_%p;\n", node, node->left);
        node_dump(node->left);
    }
    else
    {
        printf("\tL_NULL_%p[label=\"NULL\", color=\"red\"];\n", node);
        printf("\tnode_%p:<f0>->L_NULL_%p;\n", node, node);
    }
    if(node->right)
    {
        printf("\tnode_%p:<f1>->node_%p;\n", node, node->right);
        node_dump(node->right);
    }
    else
    {
        printf("\tR_NULL_%p[label=\"NULL\", color=\"red\"];\n", node);
        printf("\tnode_%p:<f1>->R_NULL_%p;\n", node, node);
    }
    
    return;
}

void tree_dump(struct tree_node *node)
{
    freopen("tree_graph/bi_tree_graph.dot", "w", stdout);

    printf("digraph tree{\n");
    printf("\trankdir=TB;\n");
    node_dump(node);
    printf("}\n");
    
}
