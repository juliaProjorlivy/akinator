#ifndef BI_TREE_READER_H
#define BI_TREE_READER_H

#include "bi_tree.h"

struct tree_node **in_tree_reader(const char **line, struct tree_node **node); // returns the root of the tree

int read_value(const char **line, char *val);

#endif
