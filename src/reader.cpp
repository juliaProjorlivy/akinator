#include "reader.h"
#include "ctor_dtor.h"
#include "verror.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const  int max_length = 100;

int print_in_file(const char *filename, const char *line)
{
    FILE *file = fopen(filename, "w");
    if(!file)
    {
        VERROR_FOPEN(filename);
        return 1;
    }
    if(fprintf(file, "%s", line) < 0)
    {
        VERROR_FWRITE(filename);
        return 1;
    }
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
            node->value = strdup(val);
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
    
