#include "bi_tree_ctor_dtor.h"
#include "bi_tree_dump.h"
#include "bi_tree_func.h"

int main()
{
    struct tree_node *root = New(0);
    struct tree_node *keeper = add_node(root, 9);
    add_node(keeper, -2);
    print_in_node(root);

    Del(root);

    return 0;
}

