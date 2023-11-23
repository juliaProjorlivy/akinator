#include "bi_tree_reader.h"
#include "bi_tree_ctor_dtor.h"
#include "verror.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const  int max_length = 100;

int print_in_file(const char *filename, const char *line)
{
    FILE *file = fopen(filename, "w");
    fprintf(file, "%s", line);
    if(fclose(file))
    {
        VERROR_FCLOSE(filename);
        return 1;
    }
    return 0;
}

int read_value(const char **line, char *val)
{
    int word_len = 0;
    int cur_len = 0;

    do
    {
        if(!sscanf(*line, "%s %n", val + cur_len, &word_len))
        {
            VERROR_SSCANF(*line);
            return 1;
        }
        *line += word_len;
        cur_len += word_len;
        val[cur_len - 1] = ' '; // because of space character
    
    } while (**line != '\"');
    (*line)++;
    if(**line != ' ')
    {
        VERROR("incorrect syntax");
        return 1;
    }
    (*line)++;
    val[cur_len - 2] = '\0';

    return 0;
}


struct tree_node *in_tree_reader(const char **line) // returns the root of the tree
{    
    while(**line == ' ')
    {
        (*line)++;
    }
    if(**line == '(')
    {
        (*line)++;
        if(**line != ' ')
        {
            VERROR("incorrect syntax");
            return NULL;
        }
        (*line)++;
        struct tree_node *node = Node(NULL);
        node->left = in_tree_reader(line);
        if(**line == '\"')
        {
            (*line)++;
            char val[max_length] = {};
            if(read_value(line, val))
            {
                VERROR_SSCANF(*line);
                return NULL;
            }
            node->value = strndup(val, strlen(val));
        }
        node->right = in_tree_reader(line);
        if(**line != ')')
        {
            VERROR("incorrect sentence structure");
            return NULL;
        }
        (*line)++;
        while(**line == ' ')
        {
            (*line)++;
        }
        return node;
    }
   
    return NULL;
}

    // TODO: skip_spaces(line) -> *line == '('

        // else if(!strcmp("\"", l_val)) // if it is not nil and not a bracket -> its some value
        // {
        //     // line[\""] = \0;
        //     // " lily\0"

        //     // "aaa \0\0b ccc 9"

        //     // strtok(line, "b9");
        //     // ptr -> "aaa \0"

        //     // strtok(NULL, "\")(")
        //     // ptr -> "\0"

        //     // strtok(NULL, "9")
        //     // ptr -> "b ccc \0"

        //     read_value(line, l_val);
        //     node->left = New(l_val);
        // }
        
