#include "akinator.h"
#include "bi_tree_ctor_dtor.h"
#include "bi_tree_reader.h"
#include "bi_tree_func.h"
#include "bi_tree_dump.h"
#include "verror.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int max_words = 100;
const int max_len = 100;
const char space = 32;

void free_words(char **words, int n_words)
{
    for(int i = 0; i < n_words; i++)
    {
        free(words[i]);
    }
    free(words);
}


const char *NOT = "not ";
const size_t len_not = strlen(NOT);

char **define(struct tree_node *node, const char *line, int *w_count)
{
    if(!node)
    {
        return NULL;
    }
    if(!strcmp(node->value, line))
    {
        char **words = (char **)calloc(sizeof(char *), max_words);
        if(!words)
        {
            VERROR_MEM;
            return NULL;
        }
        for(int i = 0; i < max_words; i++)
        {
            words[i] = (char *)calloc(sizeof(char), max_len);
            if(!words[i])
            {
                free_words(words, i);
                VERROR_MEM;
                return NULL;
            }
        }
        return words;
    }


    char **words_l = define(node->left, line, w_count);

    char **words_r = define(node->right, line, w_count);

    char **words = (!words_r) ? words_l : words_r;
    
    if(words)
    {
        size_t add_not = 0;
        if(words_r)
        {
            strncpy(*(words + *w_count), NOT, len_not);
            add_not += len_not;
        }
        strncpy(*(words + *w_count) + add_not, node->value, strlen(node->value));
        (*w_count)++;
        return words; 
    }
    
    return NULL;
}

void print_definition(const char *line, char **words, int w_count)
{
    printf("%s is ", line);
    for(int i = 0; i < w_count; i++)
    {
        printf("%s and ", words[i]);
    }
    printf("...\n");
}

struct tree_node *find(struct tree_node *node) // retruns the last node that contains not null left and right childrens
{
    if(!node)
    {
        return NULL;
    }
    
    int answer = 0;
    printf("%s?\n", node->value);
    scanf(" %d", &answer);
   
    struct tree_node *not_found = answer ? find(node->left) : find(node->right);

    if(!not_found)
    {
        printf("Is it %s?\n", node->value);
        int concl_ans = 0;
        scanf(" %d", &concl_ans);
        if(concl_ans)
        {
            printf("I knew it!\n");
            return node;
        }

        printf("Who is it then?\n");
        char new_val[max_len] = {};
        scanf(" %[^\n]s", new_val);
        printf("%s\n", new_val);

        printf("Should I add \"%s\" to the data?\n", new_val);
        scanf(" %d", &concl_ans);
        if(!concl_ans)
        {
            return node;
        }

        char old_val[max_len] = {};
        char repl_val[max_len] = {};
        printf("What %s differs from %s?\n", new_val, node->value);// reply value could be more than just one word
        scanf(" %[^\n]s", repl_val);

        strncpy(old_val, node->value, strlen(node->value));
        strncpy(node->value, repl_val, strlen(repl_val));
        node->value[strlen(repl_val)] = 0;
        node->right = New(old_val);
        node->left = New(new_val);
    }
    
    return node;
   
}

typedef enum
{
    FIND = 102,
    DEFINE = 100,
    QUIT = 113,
} options;

int akinator(struct tree_node *root)
{
    printf("find define quit\n%2c %6c %6c\n", 'f', 'd', 'q');
    char option = 0;
    scanf(" %c", &option);
    switch ((int)option)
    {
    case FIND:
    {
        find(root);
        akinator(root);
        break;
    }
    case DEFINE:
    {
        printf("Enter a searching word:\n");
        int w_count = 0;
        char obj[max_len] = {};
        scanf(" %[^\n]s", obj);
        char **words = define(root, obj, &w_count);
        if(!words)
        {
            printf("The definition wasn't found\n");
        }
        else
        {
            print_definition(obj, words, w_count);
            free_words(words, max_words);
        }
        akinator(root);
    }
    default:
    {
        return 0;
    }
    }
    
    return 0;

}





