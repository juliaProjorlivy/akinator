#include "bi_tree_ctor_dtor.h"
#include "bi_tree_dump.h"
#include "bi_tree_func.h"
#include "bi_tree_reader.h"


int main()
{
    struct tree_node *root = New("mom went");
    struct tree_node *keeper = add_node(root, "dad");
    add_node(keeper, "dog");
    print_in_node(root);
    Del(root);
    printf("\n");

    // Del(root);
    const char *line = "( ( nil \" dad \" ( nil \" dog \" nil ) ) \" mom went \" nil )";
    // struct tree_node *new_root = New("mom went");
    struct tree_node *new_root = in_tree_reader(&line);
    // struct tree_node *keepers = add_node(new_root, "dad");
    // add_node(keepers, "dog");
    print_in_node(new_root);
    Del(new_root);
    printf("\n");

    return 0;
}

