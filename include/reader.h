#ifndef BI_TREE_READER_H
#define BI_TREE_READER_H

#include "tree.h"

struct tree_node *in_tree_reader(const char **line); // returns the root of the tree

int read_value(const char **line, char *val);

int print_in_file(const char *filename, const char *line);

#endif
