#include "bi_tree_ctor_dtor.h"
#include "bi_tree_dump.h"
#include "bi_tree_func.h"
#include "bi_tree_reader.h"
#include "akinator.h"
#include <stdlib.h>

const int sen_len = 200;
const int max_len = 30;
const int words_count = 20;

int main()
{
    const int data_size = 400;
    struct tree_node *root = New("anonimus");
    // struct tree_node *keeper = add_node(root, "dad");
    // add_node(keeper, "dog");
    // print_in_node(root);
    // printf("\n");
    // print_pre_node(root);
    // printf("\n");
    // print_post_node(root);
    // printf("\n");

   
    char *line = (char *)calloc(sizeof(char), data_size);
    char *ptr = line;
    // find(root);
    // print_in_node(root, &line);
    // printf("%s\n", ptr);
    // print_in_file("data.txt", ptr);
    akinator(root);
    Del(root);
    free(ptr);
  

    // Del(root);
    // const char *line = "( ( nil \" dad \" ( nil \" dog \" nil ) ) \" mom went \" nil )";
    // const char *pre_line = "( \" mom went \" ( \" dad \" nil ( \" dog \" nil nil ) ) nil )";
    // const char *post_line = "( ( nil ( nil nil \" dog \" ) \" dad \" ) nil \" mom went \" )";
    // // struct tree_node *new_root = New("mom went");
    // struct tree_node *new_root = in_tree_reader(&line);
    // struct tree_node *pre_new_root = pre_tree_reader(&pre_line);
    // struct tree_node *post_new_root = post_tree_reader(&post_line);
    // // struct tree_node *keepers = add_node(new_root, "dad");
    // // add_node(keepers, "dog");
    // print_in_node(new_root);
    // printf("\n");
    // print_pre_node(pre_new_root);
    // printf("\n");
    // print_post_node(post_new_root);
    // printf("\n");
    // tree_dump(new_root);
    // Del(new_root);
    // Del(post_new_root);
    // Del(pre_new_root);

    return 0;
}

