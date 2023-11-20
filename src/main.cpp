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
   
    char *line = (char *)calloc(sizeof(char), data_size);
    char *ptr_print = line;
    char *ptr_del = line;
    
    FILE *file = fopen("data.txt", "r+");
    struct stat buf;
    stat("data.txt", &buf);
    fread(line, (size_t)buf.st_size, 1, file);
    fclose(file);
    printf("filesize = %ld\n", buf.st_size);
    const char *const_line = (const char *)line;
    printf("line = %s\n", const_line);
    struct tree_node *root = in_tree_reader(&const_line);
    akinator(root);
    print_in_node(root, &ptr_print);
    print_in_file("data.txt", ptr_del);
    freopen("tree_graph/bi_tree_graph.dot", "w", stdout);
    tree_dump(root);
    Del(root);
    free(ptr_del);
    


    return 0;
}

