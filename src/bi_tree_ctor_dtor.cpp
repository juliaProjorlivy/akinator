#include "bi_tree.h"
#include "verror.h"
#include <stdlib.h>

int New(struct tree_node *node)
{
    struct tree_node *right = (struct tree_node *)calloc(sizeof(tree_node), 1);
    if(!right)
    {
        VERROR_MEM;
        return 1;
    }
}
