#include <stdio.h>
#include "akinator.h"
#include "ctor_dtor.h"
#include "reader.h"
#include "dump.h"
#include "verror.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static const int max_words = 100;
static const int max_len = 100;
static char symb_start[] = "fd";
static char symb_ask[] = "yn";

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

static void print_question(char *value) {printf("%s? [y/n/q]\n", value);}
static void print_suggestion(char *value) {printf("Should I add \"%s\" to the data? [y/n/q]\n", value);}
static void print_start(char *value) {printf("find define quit\n%s\n", value);}

int check_answer(char *answer, void (*func)(char *), char *value, char *symbols)
{
    func(value);
    scanf(" %c", answer);
    if(*answer != symbols[0] && *answer != symbols[1] && *answer != 'q')
    {
        printf("Wrong button. Try again!\n");
        check_answer(answer, func, value, symbols);
    }
    if(*answer == 'q')
    {
        printf("exiting...\n");
        return 1;
    }
    return 0;
}

struct tree_node *find(struct tree_node **node, char *answer)
{
    if(!(*node))
    {
        return NULL;
    }

    if(check_answer(answer, print_question, (*node)->value, symb_ask))
    {
        return NULL;
    }
    char prime_answer = *answer;
    
   
    struct tree_node *not_found = (prime_answer != 'n') ? find(&((*node)->left), answer) : find(&((*node)->right), answer);
    if(*answer == 'q')
    {
        printf("exiting...\n");
        return NULL;
    }
    if(prime_answer != 'n')
    {
        (*node)->left = not_found;
    }
    else
    {
        (*node)->right = not_found;
    }

    if(!not_found)
    {
        if(prime_answer == 'y')
        {
            printf("I knew it!\n");
            return *node;
        }

        printf("Who is it then?\n");
        char new_val[max_len] = {};
        int scanf_max_len = max_len;
        scanf(" %[^\n]%n", new_val, &scanf_max_len);

        if(check_answer(answer, print_suggestion, new_val, symb_ask))
        {
            return NULL;
        }
        if(*answer == 'n')
        {
            return *node;
        }

        char repl_val[max_len] = {};
        printf("What differs %s from %s?\n", new_val, (*node)->value);
        scanf(" %[^\n]%n", repl_val, &scanf_max_len);
        struct tree_node *new_node = Node(repl_val);
        new_node->left = Node(new_val);
        new_node->right = (*node);
        *node = new_node; 

    }
    
    return *node;
   
}

typedef enum
{
    FIND = 102,
    DEFINE = 100,
} options;

int akinator(struct tree_node **root)
{
    system("say \"hello my dear friend! Let's play a game. Choose the option\"");
    char option = 'q';
    char start_string[] = "f    d   q";
    check_answer(&option, print_start, start_string, symb_start);
    switch ((int)option)
    {
        case FIND:
        {
            char answer = 'y';
            find(root, &answer);
            akinator(root);
            break;
        }
        case DEFINE:
        {
            printf("Enter a searching word:\n");
            int w_count = 0;
            char obj[max_len] = {};
            int scanf_max_len = max_len;
            scanf(" %[^\n]%n", obj, &scanf_max_len);
            char **words = define(*root, obj, &w_count);
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
            break;
        }
        default:
        {
            printf("exiting...\n");
            break;
        }
    }
    
    return 0;

}





