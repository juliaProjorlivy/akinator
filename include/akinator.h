#ifndef AKINATOR_H
#define AKINATOR_H

char **define(struct tree_node *node, const char *line, int *w_count);

struct tree_node *find(struct tree_node *node);

void print_definition(const char *line, char **words, int w_count);

int akinator(struct tree_node *root);

void free_words(char **words, int n_words);

#endif
