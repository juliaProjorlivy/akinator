#include "bi_tree_reader.h"
#include "bi_tree_ctor_dtor.h"
#include "verror.h"
#include <stdio.h>

const char nil[] = "nil";
const  int max_length = 100;
const char space = 32;

// const char *line(const char *filename)
// {
//     FILE *file = fopen(filename, "r");

//     fread()
// }

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
    
    } while (strcmp(val + cur_len - word_len, "\""));

    return 0;
}

struct tree_node **in_tree_reader(const char **line, struct tree_node **node) // returns the root of the tree
{    
    int word_len = 0;
    char bracket[max_length] = {};

    if(!sscanf(*line, "%s %n", bracket, &word_len))
    {
        VERROR_SSCANF(*line);
        return NULL;
    }
    *line += word_len;

    if(!strcmp(bracket, "("))
    {
        *node = New("try it");
    }

    char l_val[max_length] = {};

    if(!sscanf(*line, "%s %n", l_val, &word_len))
    {
        VERROR_SSCANF(*line);
        return NULL;
    }
    *line += word_len;
    if(!strcmp(l_val, "("))
    {
        *line -= word_len;
        in_tree_reader(line, &((*node)->left));
    }
    if(!strcmp("\"", l_val)) // if it is not nil and not a bracket -> its some value
    {
        read_value(line, l_val);
        (*node)->left = New((const char *)l_val);
    }
    

    char val[max_length] = {}; // what if node contains several words -> in dump put values in brackets
    if(!sscanf(*line, "%s %n", val, &word_len))
    {
        VERROR_SSCANF(*line);
        return NULL;
    }
    *line += word_len; 
    if(!strcmp(val, "\""))
    {
        if(read_value(line, val))
        {
            VERROR_SSCANF(*line);
            return NULL;
        }
        (*node)->value = val;
    }

    char r_val[max_length] = {};
    if(!sscanf(*line, "%s %n", r_val, &word_len))
    {
        VERROR_SSCANF(*line);
        return NULL;
    }
    *line += word_len;

    if(!strcmp(r_val, "("))
    {
        *line -= word_len;
        in_tree_reader(line, &((*node)->right));
    }
    if(!strcmp(r_val, "\""))
    {
        if(read_value(line, r_val))
        {
            VERROR_SSCANF(*line);
            return NULL;
        }
        (*node)->right = New((const char *)r_val);
    }


    if(!sscanf(*line, "%s %n", bracket, &word_len))
    {
        VERROR_SSCANF(*line);
        return NULL;
    }
    *line += word_len;
    if(!strcmp(bracket, ")"))
    {
        return node;
    }

    return NULL;
}
