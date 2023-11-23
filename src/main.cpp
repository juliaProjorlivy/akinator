#include "bi_tree_ctor_dtor.h"
#include "bi_tree_dump.h"
#include "bi_tree_reader.h"
#include "verror.h"
#include "akinator.h"
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) // argv[1] = data.txt, argv[2] = .dot
{   
    if(argc < 3)
    {
        VERROR("too little arguments are given");
        return 1;
    }

    const char *data_filename = argv[1];
    const char *write_filename = argv[2];
    
    FILE *file = fopen(data_filename, "r+");
    struct stat buf;
    if(stat(data_filename, &buf))
    {
        VERROR("could not stat");
        return 1;
    }
    size_t data_size = (size_t)buf.st_size + 1;
    char *line = (char *)calloc(sizeof(char), data_size);
    if(line == NULL)
    {
        VERROR_MEM;
        return 1;
    }

    if(fread(line, (size_t)buf.st_size, 1, file) < 1)
    {
        VERROR_FWRITE(data_filename);
        return 1;
    } 
    if(fclose(file))
    {
        VERROR_FCLOSE(data_filename);
        return 1;
    }
    printf("line = %s\n", line);

    const char *const_line = (const char *)line;

    struct tree_node *root = in_tree_reader(&const_line);
    akinator(&root);
    const int new_data_size = 500;
    char *new_line = (char *)calloc(sizeof(char), new_data_size);
    if(!new_line)
    {
        VERROR_MEM;
        return 1;
    }
    char *new_ptr = new_line;
    print_in_node(root, &new_line);
    printf("line = %s\n", new_ptr);
    print_in_file(data_filename, new_ptr);
    tree_dump(root, write_filename);
    Del_tree(root);
    free(line);
    free(new_ptr);

    return 0;
}

