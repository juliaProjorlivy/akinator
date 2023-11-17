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

void free_words(char **words, int n_words)
{
    for(int i = 0; i < n_words; n_words--)
    {
        (*words)--;
        free(*words);
    }
    free(words);
}

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
        for(size_t i = 0; i < max_words; i++)
        {
            words[i] = (char *)calloc(sizeof(char), max_len);
            if(!words[i])
            {
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
        strncpy(*(words + *w_count), node->value, strlen(node->value));
        (*w_count)++;
        return words; 
    }
    
    return NULL;
}

void print_definition(const char *line, char **words, int w_count)
{
    printf("%s is ", line);
    for(; w_count > 0; w_count--)
    {
        printf(", %s", *words);
        (*words) -= 1;
    }
}

int find(struct tree_node *node)
{
    if(!node)
    {
        return 1;
    }
    
    int answer = 0;
    printf("%s?\n", node->value);
    scanf("%d", &answer);
    if(answer)
    {
        int is_found = find(node->left);

        if(is_found)
        {
            printf("Is it %s?\n", node->value);
            int end_ans = 0;
            scanf("%d", &end_ans);
            if(end_ans)
            {
                printf("I knew it!\n");
                return 0;
            }

            printf("Who is it then?\n");
            char new_r_val[max_len] = {};
            scanf("%s", new_r_val);

            printf("Should I add \"%s\" to the data?\n", new_r_val);
            scanf("%d", &end_ans);
            if(!end_ans)
            {
                return 0;
            }

            printf("What %s differs from %s?\n", node->value, new_r_val);
            char old_val[max_len] = {};
            char new_val[max_len] = {};

            strncpy(old_val, node->value, strlen(node->value));
            scanf("%s", new_val);
            strncpy(node->value, new_val, strlen(new_val));
            node->value[strlen(new_val)] = 0;
            node->left = New(old_val);
            node->right = New(new_r_val);

            return 0;
        }
        
        return 0;
    }

    return find(node->right);
}

typedef enum
{
    FIND = 102,
    DEFINE = 100,
    QUIT = 113,
} options;

int akinator(struct tree_node *root)
{
    printf("find define quit\n%2c %6c %13c\n", 'f', 'd', 'q');
    char option = 0;
    scanf("%c", &option);
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
        int w_count = 0;
        char obj[max_len] = {};
        scanf("%s", obj);
        char **words = define(root, obj, &w_count);
        if(!words)
        {
            printf("The definition wasn't found\n");
        }
        else
        {
            print_definition(obj, words, w_count);
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





