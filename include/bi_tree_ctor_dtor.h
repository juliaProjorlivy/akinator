#ifndef BI_TREE_CTOR_DTOR_H
#define BI_TREE_CTOR_DTOR_H

#include "bi_tree.h"

struct tree_node *New(elem_t val);

void Del(struct tree_node *node);

#endif
