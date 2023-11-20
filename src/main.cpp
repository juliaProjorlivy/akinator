#include "bi_tree_ctor_dtor.h"
#include "bi_tree_dump.h"
#include "bi_tree_func.h"
#include "bi_tree_reader.h"
#include "akinator.h"
#include <stdlib.h>
#include <sys/stat.h>

const int sen_len = 200;
const int max_len = 30;
const int words_count = 20;

int main()
{
    const int data_size = 400;
    // struct tree_node *root = New("anonimus");
   
    char *line = (char *)calloc(sizeof(char), data_size);
    char *ptr_print = line;
    char *ptr_del = line;

    // akinator(root);
    // Del(root);
    // free(ptr);
    
    FILE *file = fopen("data.txt", "r+");
    struct stat buf;
    stat("data.txt", &buf);
    fread(line, (size_t)buf.st_size, 1, file);
    printf("filesize = %ld\n", buf.st_size);
    // const char *const_line = (const char *)line;
    // printf("line = %s\n", const_line);
    const char *const_line = "( ( nil \" anonimus \" nil ) \" cool \" ( nil \" dad \" nil ) )";
    printf("line = %s\n", const_line);
    struct tree_node *root = in_tree_reader(&const_line);
    akinator(root);
    print_in_node(root, &ptr_print);
    print_in_file("data.txt", ptr_del);
    Del(root);
    free(ptr_del);
    

    // Del(root);
    // const char *line = "( ( nil \" dad не dad а дед!!!! \" ( nil \" dog \" nil ) ) \" mom went \" nil )";
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

